#include <stdio.h>
#include <time.h>
#include <gtk/gtk.h>
#include <cJSON.h>
#include <string.h>
#include "define.h"





// int main(int argc, char *argv[]) {
    /*
    cJSON * test_package = cJSON_CreateObject();
    struct account test_client;
    test_client = CreateAccount();
    /
    test_package = cJSON_PACKAGE_MAKE_REGISTER(test_client.usrname,
                                               test_client.passwd,
                                               test_client.nickname,
                                               test_client.description,
                                               test_client.securityQuestion,
                                               test_client.securityQuAnswer);

    test_package = cJSON_PACKAGE_MAKE_DELETE(test_client.usrname);
    printf("%s\n", cJSON_Print(test_package));
    */
    // BUTTON_CLICKED SHALL BE A FUNCTION FOR CONNECTING THE SERVER
    // IF IT DOES NOT WORK, THE LOOPS WILL KEEP GOING BACK TO WHERE THE POINT IS;
    /*
connection_point:
    if (BUTTON_CLICKED() == 1) {
        if (CONNECTION() == false) {
            goto connection_point;
        }
    } else {
        goto connection_point;
    }
     */////////////////////
    // IF CONNECTION IS DONE, SWITCH TO THE INIT PAGE
    //////SWITCHER_TO_LOGIN_AND_REGISTER_PAGE();

    //UPPER PART IS FOR CONNECTION AND SWITCH TO LOGIN PAGE
    //-----------------------------------------------------------------------//
    //子线程读
    /////pthread_create(&th, NULL, thread_control, NULL);
    ///// int times = 100;
    //主线程写
    /////while (true) {////
    /*
    scanf("%s", sendbuf);
    send(sockfd, sendbuf, strlen(sendbuf), 0);
    memset(sendbuf, 0, sizeof(sendbuf));
    */
    ///    if (times--) break;/////
    /*
    if (CONNECTION() == false) {
        printf("CONNECTION FAILED.\n");
    }

    cJSON *test = cJSON_CreateObject();
    test = PRE_STRUCTURE("fetch_mail");
    cJSON *CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(test, "content", CONTENT);

    send(sockfd, cJSON_PrintUnformatted(test), strlen(cJSON_PrintUnformatted(test)), 0);
    int REC = 0, REC_ORIGIN = 0;
    // char rec_test[5] = {"\0"};
    char rec_origin[100] = {'\0'};
    REC_ORIGIN = recv(sockfd, rec_origin, sizeof(rec_origin), 0);

    if (REC_ORIGIN > 0) {
        printf("%s\n", rec_origin);
    } else {
        printf("receive nothing\n");
    }
    memset(rec_origin, '\0', sizeof(rec_origin));
    REC = recv(sockfd, rec_origin, sizeof(rec_origin), 0);
    if (REC > 0) {
        printf("%s\n", rec_origin);
    } else {
        printf("receive nothing\n");
    }
    */




    //return 0;
// }

GtkWidget* window;
GtkWidget* table_main;
GtkWidget* label_greet;
GtkWidget* table_write;
GtkWidget* table_inbox;
GtkWidget* table_contact;
GtkWidget* table_sent;
GtkWidget* table_draft;
GtkWidget* table_dustbin;

GtkWidget* entry_addressee;
GtkWidget* entry_subject;
GtkWidget* textview;


int state;                         			//current table

void deal_button(GtkButton* button, gpointer data);
void data_button(GtkButton* button, gpointer data);

GtkWidget* init_greet_label(){
    GtkWidget* label=gtk_label_new("");
    time_t timer;
    struct tm* tblock;
    char temp[50];

    time(&timer);
    tblock=gmtime(&timer);
    sprintf(temp, "%d/%d/%d\n", tblock->tm_year+1900, tblock->tm_mon+1, tblock->tm_mday);
    if(tblock->tm_hour+8<12) strcat(temp, "Good Morning!xxx");
    else if(tblock->tm_hour+8<18) strcat(temp, "Good Afternoon!xxx");
    else strcat(temp,"Good evening!\n");
    printf("%s\n", temp);
    gtk_label_set_text(GTK_LABEL(label), temp);
    return label;
}

GtkWidget* init_write_table(){
//	create write table
    GtkWidget* table=gtk_table_new(10,6,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 15);
    gtk_table_set_col_spacings(GTK_TABLE(table), 20);

    GtkWidget* scrolledwindow=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);


//	create labels
    GtkWidget* label_addressee=gtk_label_new("Addressee");
    GtkWidget* label_subject=gtk_label_new("Subject");
    GtkWidget* label_text=gtk_label_new("Text");

//	create entries/textviews
    entry_addressee=gtk_entry_new();
    entry_subject=gtk_entry_new();
    textview=gtk_text_view_new();

//	create buttons
    GtkWidget* button_submit=gtk_button_new_with_label("Submit");
    GtkWidget* button_save=gtk_button_new_with_label("Save");

//	connect callback function for data process
    g_signal_connect(button_save, "clicked",G_CALLBACK(data_button), "Save");
    g_signal_connect(button_submit, "clicked",G_CALLBACK(data_button), "Submit");

    gtk_container_add(GTK_CONTAINER(scrolledwindow), textview);
    gtk_table_attach_defaults(GTK_TABLE(table), label_addressee,0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table), label_subject,0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table), label_text,0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table), entry_addressee,1,5,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table), entry_subject,1,5,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table), scrolledwindow,1,5,2,9);
    gtk_table_attach_defaults(GTK_TABLE(table), button_save,3,4,9,10);
    gtk_table_attach_defaults(GTK_TABLE(table), button_submit,4,5,9,10);

    return table;
}

GtkWidget* init_inbox_table(){
    GtkWidget* table=gtk_table_new(7,6,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    gtk_table_set_col_spacings(GTK_TABLE(table), 10);

    GtkWidget* button_mails[6];
    GtkWidget* button_delete=gtk_button_new_with_label("Delete");
    GtkWidget* button_open=gtk_button_new_with_label("Open");
    for(int i=0;i<6;i++){
        button_mails[i]=gtk_button_new_with_label("hello");
    }
    for(int i=0;i<6;i++) gtk_table_attach_defaults(GTK_TABLE(table), button_mails[i], 0,5,i,i+1);
    gtk_table_attach_defaults(GTK_TABLE(table), button_delete, 3,4,6,7);
    gtk_table_attach_defaults(GTK_TABLE(table), button_open, 4,5,6,7);
    return table;
}

GtkWidget* init_contact_table(){
    GtkWidget* table=gtk_table_new(7,6,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    gtk_table_set_col_spacings(GTK_TABLE(table), 10);

    GtkWidget* button_contact[6];
    GtkWidget* button_delete=gtk_button_new_with_label("Delete");
    GtkWidget* button_reply=gtk_button_new_with_label("Reply");
    for(int i=0;i<6;i++){
        button_contact[i]=gtk_button_new_with_label("Contact");
    }
    for(int i=0;i<6;i++) gtk_table_attach_defaults(GTK_TABLE(table), button_contact[i], 0,5,i,i+1);
    gtk_table_attach_defaults(GTK_TABLE(table), button_delete, 3,4,6,7);
    gtk_table_attach_defaults(GTK_TABLE(table), button_reply, 4,5,6,7);
    return table;
}

GtkWidget* init_sent_table(){
    GtkWidget* table=gtk_table_new(7,6,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    gtk_table_set_col_spacings(GTK_TABLE(table), 10);

    GtkWidget* button_sent[6];
    GtkWidget* button_delete=gtk_button_new_with_label("Delete");
    GtkWidget* button_open=gtk_button_new_with_label("open");
    for(int i=0;i<6;i++){
        button_sent[i]=gtk_button_new_with_label("Sent");
    }
    for(int i=0;i<6;i++) gtk_table_attach_defaults(GTK_TABLE(table), button_sent[i], 0,5,i,i+1);
    gtk_table_attach_defaults(GTK_TABLE(table), button_delete, 3,4,6,7);
    gtk_table_attach_defaults(GTK_TABLE(table), button_open, 4,5,6,7);
    return table;
}

GtkWidget* init_draft_table(){

}

GtkWidget* init_dustbin_table(){
    GtkWidget* table=gtk_table_new(7,6,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    gtk_table_set_col_spacings(GTK_TABLE(table), 10);

    GtkWidget* button_dustbin[6];
    GtkWidget* button_delete=gtk_button_new_with_label("Delete");
    GtkWidget* button_recover=gtk_button_new_with_label("Recover");
    for(int i=0;i<6;i++){
        button_dustbin[i]=gtk_button_new_with_label("Dustbin");
    }
    for(int i=0;i<6;i++) gtk_table_attach_defaults(GTK_TABLE(table), button_dustbin[i], 0,5,i,i+1);
    gtk_table_attach_defaults(GTK_TABLE(table), button_delete, 3,4,6,7);
    gtk_table_attach_defaults(GTK_TABLE(table), button_recover, 4,5,6,7);
    return table;
}

GtkWidget* init_main_table(void){
//	create main table
    GtkWidget* table=gtk_table_new(8,8,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    gtk_table_set_col_spacings(GTK_TABLE(table), 10);

//	create a label
    GtkWidget* label_user=gtk_label_new("xxxx@bit.com\nMotto: Good*2 study! Day*2 up!");
    //label_greet=gtk_label_new("Good Moring! xxx\nInbox(xx)");
    label_greet=init_greet_label();
    gtk_table_attach_defaults(GTK_TABLE(table), label_user, 0,2,1,2 );
    gtk_table_attach_defaults(GTK_TABLE(table), label_greet, 2,7,2,7);

//	create buttons
    GtkWidget* button_email=gtk_button_new_with_label("BIT Email System");
    GtkWidget* button_write=gtk_button_new_with_label("Write");
    GtkWidget* button_inbox=gtk_button_new_with_label("Inbox");
    GtkWidget* button_contact=gtk_button_new_with_label("Contact");
    GtkWidget* button_sent=gtk_button_new_with_label("Sent");
    GtkWidget* button_drafts=gtk_button_new_with_label("Drafts");
    GtkWidget* button_dustbin=gtk_button_new_with_label("Dustbin");
    GtkWidget* button_logout=gtk_button_new_with_label("Logout");
    gtk_button_set_relief(GTK_BUTTON(button_email), GTK_RELIEF_NONE);

//	connect callback function for panel change
    g_signal_connect(button_write, "clicked",G_CALLBACK(deal_button), "Write");
    g_signal_connect(button_inbox, "clicked",G_CALLBACK(deal_button), "Inbox");
    g_signal_connect(button_contact, "clicked",G_CALLBACK(deal_button), "Contact");
    g_signal_connect(button_email, "clicked",G_CALLBACK(deal_button), "Back");
    g_signal_connect(button_sent, "clicked",G_CALLBACK(deal_button), "Sent");

    g_signal_connect(button_dustbin, "clicked",G_CALLBACK(deal_button), "Dustbin");

    gtk_table_attach_defaults(GTK_TABLE(table), button_email, 0,2,0,1 );
    gtk_table_attach_defaults(GTK_TABLE(table), button_write, 0,1,2,3 );
    gtk_table_attach_defaults(GTK_TABLE(table), button_inbox, 0,1,3,4 );
    gtk_table_attach_defaults(GTK_TABLE(table), button_contact, 0,1,4,5 );
    gtk_table_attach_defaults(GTK_TABLE(table), button_sent, 0,1,5,6 );
    gtk_table_attach_defaults(GTK_TABLE(table), button_drafts, 0,1,6,7 );
    gtk_table_attach_defaults(GTK_TABLE(table), button_dustbin, 0,1,7,8 );
    gtk_table_attach_defaults(GTK_TABLE(table), button_logout, 7,8,0,1 );
    return table;
}
void deal_button(GtkButton* button, gpointer data){
    char* text=(char*) data;
    printf("%c %ld\n", text[0], strlen(text));
    switch(state){
        case 0: gtk_container_remove(GTK_CONTAINER(table_main), label_greet);break;
        case 1: gtk_container_remove(GTK_CONTAINER(table_main), table_write);break;
        case 2: gtk_container_remove(GTK_CONTAINER(table_main), table_inbox);break;
        case 3: gtk_container_remove(GTK_CONTAINER(table_main), table_contact); break;
        case 4: gtk_container_remove(GTK_CONTAINER(table_main), table_sent); break;

        case 6: gtk_container_remove(GTK_CONTAINER(table_main), table_dustbin); break;
        defaults: break;
    }

    if(!strcmp(text, "Back")){
        printf("Back\n");
        label_greet=init_greet_label();
        gtk_table_attach_defaults(GTK_TABLE(table_main), label_greet, 2,7,2,7); state=0;
    }
    else if(!strcmp(text, "Write")){
        printf("Write\n");
        table_write=init_write_table();
        gtk_table_attach_defaults(GTK_TABLE(table_main), table_write, 1,8,2,8); state=1;
    }else if(!strcmp(text, "Inbox")){
        printf("Inbox\n");
        table_inbox=init_inbox_table();
        gtk_table_attach_defaults(GTK_TABLE(table_main), table_inbox, 2,8,2,8); state=2;
    }else if(!strcmp(text,"Contact")){
        printf("Contact");
        table_contact=init_contact_table();
        gtk_table_attach_defaults(GTK_TABLE(table_main), table_contact, 2,8,2,8); state=3;
    }else if(!strcmp(text,"Sent")){
        printf("Sent");
        table_sent=init_sent_table();
        gtk_table_attach_defaults(GTK_TABLE(table_main), table_sent, 2,8,2,8); state=4;
    }else if(!strcmp(text, "Dustbin")){
        printf("Dustbin");
        table_dustbin=init_dustbin_table();
        gtk_table_attach_defaults(GTK_TABLE(table_main), table_dustbin, 2,8,2,8); state=6;
    }
    printf("state: %d %d\n", state, text[0]=='B');
    gtk_widget_show_all(window);

}

///
/// \param button
/// \param data



void data_button(GtkButton* button, gpointer data){
    const char* text=gtk_button_get_label(button);
    if(state==1){
        const char* recipient=gtk_entry_get_text(GTK_ENTRY(entry_addressee));
        const char* title=gtk_entry_get_text(GTK_ENTRY(entry_subject));

        GtkTextIter start, end;
        GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));

        gtk_text_buffer_get_bounds (buffer, &start, &end);
        char* text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
        printf("%s%s%s\n",recipient, title, text);
        g_free(text);

        if(!strcmp(text,"Submit")){
            if(!strlen(recipient)||!strlen(title)||!strlen(text))
                return;
        }

        cJSON * root =  cJSON_CreateObject();
        cJSON_AddItemToObject(root, "recipient", cJSON_CreateString(recipient));
        cJSON_AddItemToObject(root, "title", cJSON_CreateString(title));
        cJSON_AddItemToObject(root, "body", cJSON_CreateString(text));
        SENDER_UI_DATA_SUBMIT_BUTTON_CLICKED(root);
    }
}

void set_window(GtkWidget* window){
    gtk_window_set_title(GTK_WINDOW(window), "Bit Email");
    gtk_window_set_default_size(GTK_WINDOW(window), 1500,1100);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add(GTK_CONTAINER(window), table_main);
    gtk_widget_show_all(window);
}

/*
int main(int argc, char *argv[]) {
    //初始化
    gtk_init(&argc, &argv);

//	create main_table
    table_main=init_main_table();``

//	create window
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    set_window(window);
    state=0;

    gtk_main();
}*/

