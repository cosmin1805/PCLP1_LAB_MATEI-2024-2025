#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    char *nume;
    char *mail;
} TContact;
typedef struct
{
    TContact *src, *dest;
    char *mesaj;
    int data;
    struct TMail *replyof;
} TMail;
typedef struct
{
    int nrMaxMails, nrCrtMails, nrMaxContacts, nrCrtContacts;
    TMail *mails;
    TContact *contacts;
} TClient;
TClient *allocTClient(int nrMaxMails, int nrMaxContacts)
{
    TClient *client = (TClient *)malloc(sizeof(TClient));
    if (client == NULL)
    {
        return NULL;
    }
    client->mails = (TMail *)malloc(nrMaxMails * sizeof(TMail));
    if (client->mails == NULL)
    {
        free(client);
        return NULL;
    }
    client->contacts = (TContact *)malloc(nrMaxContacts * sizeof(TContact));
    if (client->contacts == NULL)
    {
        free(client->mails);
        free(client);
        return NULL;
    }
    client->nrCrtContacts = 0;
    client->nrMaxContacts = nrMaxContacts;
    client->nrCrtMails = 0;
    client->nrMaxMails = nrMaxMails;
    return client;
}
TContact *getContact(TClient *c, char *mail)
{
    for (int i = 0; i < c->nrCrtContacts; i++)
    {
        if (strcmp(c->contacts[i].mail, mail) == 0)
        {
            return c->contacts + i;
        }
    }
    if (c->nrCrtContacts == c->nrMaxContacts)
    {
        c->contacts = realloc(c->contacts, (c->nrCrtContacts + 1) * sizeof(TContact));
    }
    c->contacts[c->nrCrtContacts].mail = malloc(strlen(mail));
    if (c->contacts[c->nrCrtContacts].mail == NULL)
    {
        return NULL;
    }
    strcpy(c->contacts[c->nrCrtContacts++].mail, mail);
    return c->contacts + (c->nrCrtContacts - 1);
}
TMail *writeMail(TClient *c, char *mailSrc, char *mailDest, char *mesaj, TMail *replyTo)
{
    if (c->nrCrtMails == c->nrMaxMails)
    {
        return NULL;
    }
    c->mails[c->nrCrtMails].dest = getContact(c, mailDest);
    if (c->mails[c->nrCrtMails].dest == NULL)
    {
        return NULL;
    }
    c->mails[c->nrCrtMails].src = getContact(c, mailSrc);
    if (c->mails[c->nrCrtMails].src == NULL)
    {
        free(c->mails[c->nrCrtMails].dest);
        return NULL;
    }
    c->mails[c->nrCrtMails].mesaj = (char *)malloc(strlen(mesaj));
    if (c->mails[c->nrCrtMails].mesaj == NULL)
    {
        free(c->mails[c->nrCrtMails].dest);
        free(c->mails[c->nrCrtMails].src);
        return NULL;
    }
    strcpy(c->mails[c->nrCrtMails].mesaj, mesaj);
    c->mails[c->nrCrtMails++].replyof = (struct TMail *)replyTo; // ??????? ar trb sa fie asa sau ce e replyTo?
    return c->mails + (c->nrCrtMails - 1);
}
void goDeeper(TClient *c, TMail *mail, int howDeep)
{
    TMail *tempMails[c->nrCrtMails];
    int indexTempMails = 0;
    for (int i = 0; i < c->nrCrtMails; i++)
    {
        if (c->mails[i].replyof != NULL && (TMail *)c->mails[i].replyof == (TMail *)mail)
        {
            tempMails[indexTempMails++] = c->mails + i;
        }
    }
    for (int i = 0; i < indexTempMails; i++)
    {
        for (int j = i + 1; j < indexTempMails; j++)
        {
            if (tempMails[i]->data > tempMails[j]->data)
            {
                TMail *temp = tempMails[i];
                tempMails[j] = tempMails[i];
                tempMails[j] = temp;
            }
        }
    }
    for (int i = 0; i < indexTempMails; i++)
    {
        for (int j = 0; j < howDeep; j++)
        {
            printf("    ");
        }
        printf("from: %s to %s: text reply %d data:%d\n", tempMails[i]->src->mail, tempMails[i]->dest->mail, i, tempMails[i]->data);
        goDeeper(c,tempMails[i],howDeep + 1);
    }
}
void freeTot(TClient * client) {
    free(client->contacts);
    free(client->mails);
    free(client);
}
void AfiThread(TClient *c, TMail *mail)
{
    while (mail->replyof != NULL)
    {
        mail = (TMail *)mail->replyof;
    }
    printf("from: %s to %s: %s\n", mail->src->mail, mail->dest->mail, mail->mesaj);
    goDeeper(c,mail,1);
}

int main()
{
    TClient *client = allocTClient(10, 10); // Adjust the values as needed

    TMail *mail1 = writeMail(client, "vlad@cs.pub.ro", "student@cs.pub.ro", "Hello Student", NULL);
    TMail *mail2 = writeMail(client, "student@cs.pub.ro", "vlad@cs.pub.ro", "Replying to Alice!", mail1);
    TMail *mail3 = writeMail(client, "john@example.com", "alice@example.com", "Another message to Alice!", NULL);
    TMail *mail4 = writeMail(client, "vlad@cs.pub.ro", "student@cs.pub.ro", "Replying to John!", mail2);
    TMail *mail5 = writeMail(client, "student@cs.pub.ro", "vlad@cs.pub.ro", "Replying to John!", mail1);

    printf("Thread for mail1:\n");
    AfiThread(client, mail1);
    freeTot(client);
    return 0;
}
