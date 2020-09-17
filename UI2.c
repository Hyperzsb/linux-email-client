//
// Created by guangtao on 2020/9/17.
//

//
// Created by guangtao on 2020/9/16.
//

#include "UI2.h"

// check_function_part
// ________________________________________
int laststate = 0;
GtkWidget *entry_username;
GtkWidget *entry_search;
GtkWidget *entry_remark;
GtkWidget *table_read;

void check(char *username, char *password)//登录验证
{
    int flag1 = 0;
    int flag2 = 0;
    int len = strlen(password);
    if (len < 6 || len > 12) Fail_login_1();
    else {
        for (int i = 0; i < len; i++) {
            if (password[i] >= '0' && password[i] <= '9')
                flag1 = 1;
            if ((password[i] >= 'a' && password[i] <= 'z') || (password[i] >= 'A' && password[i] <= 'Z'))
                flag2 = 1;
        }
        if (flag1 * flag2 == 0) Fail_login_1();
        else {
            //sendto_sql连接数据库，0用户名不存在，1密码不正确，2进入邮箱主界面，else系统错误
            //int send=sendto_sql();
            int send = SIGN_WHOLE_PROCESS(LOGGER, password);
            if (send == 2) {
                Fail_login_2();
            } else if (send == 3) {
                Fail_login_3();
            } else if (send == 1) {
                main_mail(0, 0);
            } else System_false();
        }
    }
}

// client_function_part
// ________________________________________


GtkWidget* window;
GtkWidget* table_main;
GtkWidget* notebook;
GtkWidget* table_home;
GtkWidget* table_write;
GtkWidget* table_inbox;
GtkWidget* table_contact;
GtkWidget* table_sent;
GtkWidget* table_draft;
GtkWidget* table_dustbin;
GtkWidget* scrolled_inbox;
GtkWidget* scrolled_contact;
GtkWidget* scrolled_sent;
GtkWidget* scrolled_draft;
GtkWidget* scrolled_dustbin;
GtkWidget* scrolledtext;

GtkWidget* entry_addressee;
GtkWidget* entry_subject;
GtkWidget* textview;
GtkWidget* entry_remark;
GtkWidget* entry_username;
GtkWidget* entry_search;

int state;
int button_num;
int page_num;
int flag_search;



GtkWidget* greet_label(){
    GtkWidget* label=gtk_label_new("");
    time_t timer;
    struct tm* tblock;
    char temp[50];

    time(&timer);
    tblock=gmtime(&timer);
    sprintf(temp, "%d/%d/%d\n", tblock->tm_year+1900, tblock->tm_mon+1, tblock->tm_mday);
    strcat(temp, "Thursday\n");
    if(tblock->tm_hour+8<12) strcat(temp, "Good Morning!\n");
    else if(tblock->tm_hour+8<18) strcat(temp, "Good Afternoon!\n");
    else strcat(temp,"Good evening!\n");

    printf("%s\n", temp);
    gtk_label_set_text(GTK_LABEL(label), temp);

    return label;
}

GtkWidget* write_table(){
//	create write table
    GtkWidget* table=gtk_table_new(10,6,TRUE);

    gtk_table_set_row_spacings(GTK_TABLE(table), 15);
    gtk_table_set_col_spacings(GTK_TABLE(table), 20);

    scrolledtext=gtk_scrolled_window_new(NULL,NULL);
    GtkWidget* button_clear=gtk_button_new_with_label("Clear");
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledtext),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

//	create labels
    GtkWidget* label_addressee=gtk_label_new("Contactor");
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
    g_signal_connect(button_save, "clicked",G_CALLBACK(write_button), "Save");
    g_signal_connect(button_submit, "clicked",G_CALLBACK(write_button), "Submit");
    g_signal_connect(button_clear,"clicked",G_CALLBACK(clear_input),NULL);

    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledtext), textview);
    gtk_table_attach_defaults(GTK_TABLE(table), button_clear,1,2,8,9);
    gtk_table_attach_defaults(GTK_TABLE(table), label_addressee,0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table), label_subject,0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table), label_text,0,1,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table), entry_addressee,1,5,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table), entry_subject,1,5,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table), scrolledtext,1,5,3,8);
    gtk_table_attach_defaults(GTK_TABLE(table), button_save,3,4,8,9);
    gtk_table_attach_defaults(GTK_TABLE(table), button_submit,4,5,8,9);

    return table;

}

GtkWidget* get_scrolledwindow(const char* cmd){
    char label[200];
    int size=0, flag=0;
    GtkWidget* scrolled=gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    printf("cmd: %s\n", cmd);
    if(!strcmp(cmd, "Inbox")){
        /* fetch & get EMAIL_FROM_CONTENT*/
        cJSON *COMMAND_PACKAGE = PRE_STRUCTURE("fetch_mail");
        cJSON *CONTENT = cJSON_CreateObject();
        cJSON_AddItemToObject(CONTENT, "type", cJSON_CreateString("inbox"));
        cJSON_AddItemToObject(COMMAND_PACKAGE, "content", CONTENT);

        if (FETCH_BUTTON_CLICKED(COMMAND_PACKAGE, "inbox")) {
            printf("PACKAGE_GET_SUCCESS\n");
        } else {
            printf("ERROR_GET_PACKAGE\n");
        }
        size=size_inbox; flag=2;

    }else if(!strcmp(cmd, "Contact")){
        /* fetch & get FRIEND_LIST*/
        GET_CONTACT_BUTTON_CLICKED();
        size=size_contact; flag=3;

    }else if(!strcmp(cmd, "Sent")){
        /* fetch & get SENT_FROM_CONTENT*/
        cJSON *COMMAND_PACKAGE = PRE_STRUCTURE("fetch_mail");
        cJSON *CONTENT = cJSON_CreateObject();
        cJSON_AddItemToObject(CONTENT, "type", cJSON_CreateString("outbox"));
        cJSON_AddItemToObject(COMMAND_PACKAGE, "content", CONTENT);

        if (FETCH_BUTTON_CLICKED(COMMAND_PACKAGE, "outbox")) {
            printf("PACKAGE_GET_SUCCESS\n");
        } else {
            printf("ERROR_GET_PACKAGE\n");
        }
        size=size_sent; flag=4;
    }else if(!strcmp(cmd, "Draft")){
        /* fetch & get DRAFT_FROM_CONTENT*/
        FETCH_DRAFT_BUTTON_CLICKED();
        size=size_draft; flag=5;
    }else if(!strcmp(cmd, "Dustbin")){
        /* fetch & get EMAIL_FROM_CONTENT*/
        //size=size_dustbin; flag=6;
    }

    GtkWidget* table=gtk_table_new(size, 6, TRUE);
    GtkWidget* button[size+1];
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);

    for(int i=0; i<size; i++){
        switch(flag){
            case 2: sprintf(label,"Contactor: %s   		Title: %s",EMAIL_FROM_PACKAGE[i].contactor, EMAIL_FROM_PACKAGE[i].title);break;
            case 3: sprintf(label,"Remark: %s   		Username: %s",FRIEND_LIST[i].remark, FRIEND_LIST[i].username);break;
            case 4: sprintf(label,"Contactor: %s   		Title: %s",SENT_FROM_PACKAGE[i].contactor, SENT_FROM_PACKAGE[i].title); break;
            case 5: sprintf(label,"Contactor: %s   		Title: %s",DRAFT_FROM_PACKAGE[i].contactor, DRAFT_FROM_PACKAGE[i].title); break;
            case 6: sprintf(label,"Contactor: %s   		Title: %s",DUSTBIN_FROM_PACKAGE[i].contactor, DUSTBIN_FROM_PACKAGE[i].title);break;
        }

        button[i]=gtk_button_new_with_label(label);
        gtk_widget_set_size_request(button[i], 100,75);
        gtk_table_attach_defaults(GTK_TABLE(table), button[i],1,6,i,i+1);
        g_signal_connect(button[i],"clicked",G_CALLBACK(get_button_num),(gpointer) i);
    }
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled), table);

    return scrolled;
}

GtkWidget* inbox_table(){
    GtkWidget* table=gtk_table_new(8,6,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    gtk_table_set_col_spacings(GTK_TABLE(table), 10);

    scrolled_inbox=get_scrolledwindow("Inbox");

    entry_search=gtk_entry_new();
    GtkWidget* button_search=gtk_button_new_with_label("Search");
    GtkWidget* button_fresh=gtk_button_new_with_label("Refresh");
    GtkWidget* button_delete=gtk_button_new_with_label("Delete");
    GtkWidget* button_open=gtk_button_new_with_label("Open");

    gtk_table_attach_defaults(GTK_TABLE(table), button_search, 1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table), entry_search, 2,4,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_inbox, 0,5,1,7);
    gtk_table_attach_defaults(GTK_TABLE(table), button_fresh, 5,6,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table), button_delete, 3,4,7,8);
    gtk_table_attach_defaults(GTK_TABLE(table), button_open, 4,5,7,8);

    g_signal_connect(button_search,"clicked",G_CALLBACK(search_email_button),NULL);
    g_signal_connect(button_open,"clicked",G_CALLBACK(open_email),NULL);
    g_signal_connect(button_fresh,"clicked",G_CALLBACK(fresh_button),NULL);
    return table;
}

GtkWidget* contact_table(){
    GtkWidget* table=gtk_table_new(8,6,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    gtk_table_set_col_spacings(GTK_TABLE(table), 10);

    scrolled_contact=get_scrolledwindow("Contact");

    GtkWidget* button_fresh=gtk_button_new_with_label("Refresh");
    GtkWidget* button_add=gtk_button_new_with_label("Add");
    GtkWidget* button_reply=gtk_button_new_with_label("Reply");

    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_contact, 0,5,1,7);
    gtk_table_attach_defaults(GTK_TABLE(table), button_fresh, 5,6,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table), button_add, 3,4,7,8);
    gtk_table_attach_defaults(GTK_TABLE(table), button_reply, 4,5,7,8);

    g_signal_connect(button_add,"clicked",G_CALLBACK(add_contactor_button),NULL);
    g_signal_connect(button_reply,"clicked",G_CALLBACK(open_email),NULL);
    g_signal_connect(button_fresh,"clicked",G_CALLBACK(fresh_button),NULL);
    return table;
}

GtkWidget* sent_table(){
    GtkWidget* table=gtk_table_new(8,6,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    gtk_table_set_col_spacings(GTK_TABLE(table), 10);

    scrolled_sent=get_scrolledwindow("Sent");

    GtkWidget* button_fresh=gtk_button_new_with_label("Refresh");
    GtkWidget* button_delete=gtk_button_new_with_label("Delete");
    GtkWidget* button_open=gtk_button_new_with_label("Open");

    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_sent, 0,5,1,7);
    gtk_table_attach_defaults(GTK_TABLE(table), button_fresh, 5,6,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table), button_delete, 3,4,7,8);
    gtk_table_attach_defaults(GTK_TABLE(table), button_open, 4,5,7,8);

    g_signal_connect(button_open,"clicked",G_CALLBACK(open_email),NULL);
    g_signal_connect(button_fresh,"clicked",G_CALLBACK(fresh_button),NULL);
    return table;
}

GtkWidget* draft_table(){
    GtkWidget* table=gtk_table_new(8,6,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    gtk_table_set_col_spacings(GTK_TABLE(table), 10);

    scrolled_draft=get_scrolledwindow("Draft");

    GtkWidget* button_fresh=gtk_button_new_with_label("Refresh");
    GtkWidget* button_delete=gtk_button_new_with_label("Delete");
    GtkWidget* button_open=gtk_button_new_with_label("Edit");

    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_draft, 0,5,1,7);
    gtk_table_attach_defaults(GTK_TABLE(table), button_fresh, 5,6,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table), button_delete, 3,4,7,8);
    gtk_table_attach_defaults(GTK_TABLE(table), button_open, 4,5,7,8);

    g_signal_connect(button_open,"clicked",G_CALLBACK(open_email),NULL);
    g_signal_connect(button_fresh,"clicked",G_CALLBACK(fresh_button),NULL);
    return table;
}

GtkWidget* dustbin_table(){
    GtkWidget* table=gtk_table_new(8,6,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    gtk_table_set_col_spacings(GTK_TABLE(table), 10);

    scrolled_dustbin=get_scrolledwindow("Dustbin");

    GtkWidget* button_fresh=gtk_button_new_with_label("Refresh");
    GtkWidget* button_delete=gtk_button_new_with_label("Delete");
    GtkWidget* button_recover=gtk_button_new_with_label("Recover");

    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_dustbin, 0,5,1,7);
    gtk_table_attach_defaults(GTK_TABLE(table), button_fresh, 5,6,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table), button_delete, 3,4,7,8);
    gtk_table_attach_defaults(GTK_TABLE(table), button_recover, 4,5,7,8);

    g_signal_connect(button_fresh,"clicked",G_CALLBACK(fresh_button),NULL);

    return table;
}

GtkWidget* home_table(void){
    GtkWidget* table=gtk_table_new(6,6,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    gtk_table_set_col_spacings(GTK_TABLE(table), 10);

//	create label
    char label[100];
    sprintf(label, "Welcome back\n%s\nVirtue makes sense,\nLearning makes sense", LOGGER);
    GtkWidget* label_user=gtk_label_new(label);
    GtkWidget* label_greet=greet_label();

    GtkWidget* button_logout=gtk_button_new_with_label("Logout");

//	push label
    gtk_table_attach_defaults(GTK_TABLE(table), label_greet,1,5,1,5);
    gtk_table_attach_defaults(GTK_TABLE(table),label_user,0,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table), button_logout, 5,6,0,1);

    g_signal_connect(button_logout, "clicked", G_CALLBACK(logout_button), NULL);
    return table;
}

GtkWidget* init_notebook(void){
    GtkWidget* notebook=gtk_notebook_new();


    notebook=gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);

//	create tables
    table_home=home_table();
    table_write=write_table();
    table_inbox=inbox_table();
    table_contact=contact_table();
    table_sent=sent_table();
    table_draft=draft_table();
    table_dustbin=dustbin_table();

//	create notebook labels
    GtkWidget* label_home=gtk_label_new("Home");
    GtkWidget* label_write=gtk_label_new("Write");
    GtkWidget* label_inbox=gtk_label_new("Inbox");
    GtkWidget* label_contact=gtk_label_new("Contact");
    GtkWidget* label_sent=gtk_label_new("Sent");
    GtkWidget* label_draft=gtk_label_new("Draft");
    GtkWidget* label_dustbin=gtk_label_new("Dustbin");

    gtk_widget_set_size_request(label_home,75,50);
    gtk_widget_set_size_request(label_write,75,50);
    gtk_widget_set_size_request(label_inbox,75,50);
    gtk_widget_set_size_request(label_contact,75,50);
    gtk_widget_set_size_request(label_sent,75,50);
    gtk_widget_set_size_request(label_draft,75,50);
    gtk_widget_set_size_request(label_dustbin,75,50);

    gtk_container_set_border_width(GTK_CONTAINER(notebook), 20);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), table_home, label_home);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), table_write, label_write);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), table_inbox, label_inbox);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), table_contact, label_contact);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), table_sent, label_sent);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), table_draft, label_draft);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), table_dustbin, label_dustbin);

    g_signal_connect(notebook, "switch-page", G_CALLBACK(get_page_num), NULL);
    return notebook;
}

void read_email_popup(char* text1, char* text2, char* text3, int flag){
    GtkWidget* popup=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget* table=gtk_table_new(10,6,TRUE);

    GtkWidget* label_contactor=gtk_label_new("Contactor");
    GtkWidget* label_title=gtk_label_new("Subject");
    GtkWidget* label_text=gtk_label_new("Text");

    GtkWidget* scrolledwindow=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

//	create entries/textviews
    GtkWidget* entry_contactor=gtk_entry_new();
    GtkWidget* entry_title=gtk_entry_new();
    GtkWidget* text=gtk_text_view_new();

    GtkWidget* button_reply = gtk_button_new_with_label("Reply");
    g_signal_connect(button_reply,"clicked",G_CALLBACK(reply_email),popup);

    gtk_entry_set_text(GTK_ENTRY(entry_contactor), text1);
    gtk_entry_set_text(GTK_ENTRY(entry_title), text2);
    GtkTextBuffer *buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
    GtkTextIter iter; gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
    gtk_text_buffer_insert(buffer, &iter, text3 , -1);

//set write table
    gtk_entry_set_text(GTK_ENTRY(entry_addressee), text1);
    gtk_entry_set_text(GTK_ENTRY(entry_subject), text2);
    GtkTextBuffer* buffer1=gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    GtkTextIter iter1; gtk_text_buffer_get_iter_at_offset(buffer1, &iter1, 0);
    gtk_text_buffer_insert(buffer1, &iter1, "" , -1);
    gtk_text_buffer_insert(buffer1, &iter1, text3 , -1);


    gtk_editable_set_editable(GTK_EDITABLE(entry_contactor), FALSE);
    gtk_editable_set_editable(GTK_EDITABLE(entry_title), FALSE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text), FALSE);

    gtk_container_add(GTK_CONTAINER(popup), table);
    gtk_container_add(GTK_CONTAINER(scrolledwindow), text);

    gtk_table_attach_defaults(GTK_TABLE(table), label_contactor,0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table), label_title,0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table), label_text,0,1,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table), entry_contactor,1,5,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table), entry_title,1,5,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table), scrolledwindow,1,5,3,7);

    gtk_table_attach_defaults(GTK_TABLE(table), button_reply,4,5,8,9);

    char title[20];
    if(flag==2) strcpy(title, "Recv Email");
    else if(flag==3) strcpy(title, "Contactor");
    else if(flag==4) strcpy(title, "Sent Email");
    else if(flag==5) strcpy(title, "Draft Email");
    else if(flag==6) strcpy(title, "Dustbin Email");

    gtk_window_set_title(GTK_WINDOW(popup), title);
    gtk_widget_set_size_request(popup, 1000,800);
    gtk_window_set_position(GTK_WINDOW(popup), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(popup), FALSE);
    gtk_widget_show_all(popup);

}

void logout_confirm(GtkButton* button, gpointer data){
    gtk_widget_destroy(GTK_WIDGET(data));
    gtk_widget_destroy(window);
}

void logout_button(GtkButton* button, gpointer data){

    GtkWidget* popup=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget* table=gtk_table_new(3,3,TRUE);
    GtkWidget* button_confirm=gtk_button_new_with_label("Logout\nConfirm");

    gtk_container_add(GTK_CONTAINER(popup), table);
    gtk_table_attach_defaults(GTK_TABLE(table), button_confirm, 1,2,1,3);

    gtk_window_set_title(GTK_WINDOW(popup), "Information");
    gtk_window_set_default_size(GTK_WINDOW(popup), 200,200);
    gtk_window_set_position(GTK_WINDOW(popup), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(popup), FALSE);
    gtk_widget_show_all(popup);

    g_signal_connect(button_confirm, "clicked", G_CALLBACK(logout_confirm), popup);

}

void write_button(GtkButton* button, gpointer data){
    const char* label=(char*) data;
    gboolean flag=TRUE;

    const char* tot_recipient=gtk_entry_get_text(GTK_ENTRY(entry_addressee));
    const char* title=gtk_entry_get_text(GTK_ENTRY(entry_subject));
    char recipient[100];

    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));

    gtk_text_buffer_get_bounds (buffer, &start, &end);
    char* text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

    if(!strcmp(label,"Submit")){
        if(!strlen(tot_recipient)||!strlen(title)||!strlen(text)){
            flag=FALSE;
        }
    }

    if(flag){
        int len=strlen(tot_recipient),i=0,j=0;
        while(j<len){
            j++;
            if(tot_recipient[j]==';'){
                int len1=0;
                while(i<j) recipient[len1++]=tot_recipient[i++];
                recipient[len1]='\0';
                cJSON *root = cJSON_CreateObject();
                cJSON_AddItemToObject(root, "recipient", cJSON_CreateString(recipient));
                cJSON_AddItemToObject(root, "title", cJSON_CreateString(title));
                cJSON_AddItemToObject(root, "body", cJSON_CreateString(text));
                printf("recipient: %s, title: %s, text: %s\n", recipient, title, text);
                /* flag=send();  发送函数*/
                if (strcmp(label, "Submit") == 0) {
                    SENDER_UI_DATA_SUBMIT_BUTTON_CLICKED(LOGGER, root);
                } else {
                    SAVE_DRAFT_BUTTON_CLICKED(recipient, title, text);
                }
                /* flag=send();  发送函数*/
                i++;j++;
            }
        }

        if(i<j){
            int len1=0;
            while(i<j) recipient[len1++]=tot_recipient[i++];
            recipient[len1]='\0';
            cJSON *root = cJSON_CreateObject();
            cJSON_AddItemToObject(root, "recipient", cJSON_CreateString(recipient));
            cJSON_AddItemToObject(root, "title", cJSON_CreateString(title));
            cJSON_AddItemToObject(root, "body", cJSON_CreateString(text));
            printf("recipient: %s, title: %s, text: %s\n", recipient, title, text);
            /* flag=send();  发送函数*/
            if (strcmp(label, "Submit") == 0) {
                SENDER_UI_DATA_SUBMIT_BUTTON_CLICKED(LOGGER, root);
            } else {
                SAVE_DRAFT_BUTTON_CLICKED(recipient, title, text);
            }
            /* flag=send();  发送函数*/
        }
    }


    GtkWidget* popup=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget* label_info=gtk_label_new(flag?"Success!":"Failure");

    gtk_container_add(GTK_CONTAINER(popup), label_info);
    gtk_window_set_title(GTK_WINDOW(popup), "Information");
    gtk_widget_set_size_request(popup, 200,100);
    gtk_window_set_position(GTK_WINDOW(popup), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(popup), FALSE);
    gtk_widget_show_all(popup);
    if(flag) {
        gtk_entry_set_text(GTK_ENTRY(entry_addressee), "");
        gtk_entry_set_text(GTK_ENTRY(entry_subject), "");
        GtkTextBuffer* buffer=gtk_text_buffer_new(NULL);
        gtk_text_view_set_buffer(GTK_TEXT_VIEW(textview), buffer);
        gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook),0);
    }
}

void get_button_num(GtkButton* button, gpointer data){
    button_num=(int*) data;
    printf("button_num: %d\n", button_num);
}

void get_page_num(GtkNotebook *notebook, gpointer page, guint page_n, gpointer user_data){

    page_num=page_n;
    button_num=-1;
//	if(page_num==1){
//		gtk_entry_set_text(GTK_ENTRY(entry_addressee), "");
//		gtk_entry_set_text(GTK_ENTRY(entry_subject), "");
//		GtkTextBuffer* buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
//		GtkTextIter iter; gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
//		gtk_text_buffer_insert(buffer, &iter, "" , -1);
//	}
    printf("page_num: %d\n", page_num);
}

void open_email(GtkButton* button, gpointer data){
    if((button_num<0||page_num<=1)&&flag_search==-1) return;
    int i=flag_search!=-1?flag_search: button_num;
    printf("i: %d, page_num: %d", i, page_num);
    switch(page_num){
        case 2:	read_email_popup(EMAIL_FROM_PACKAGE[i].contactor, EMAIL_FROM_PACKAGE[i].title, EMAIL_FROM_PACKAGE[i].body, page_num); break;
        case 3:	read_email_popup(FRIEND_LIST[i].username, "", "", page_num); break;
        case 4:	read_email_popup(SENT_FROM_PACKAGE[i].contactor, SENT_FROM_PACKAGE[i].title, SENT_FROM_PACKAGE[i].body, page_num);break;
        case 5: read_email_popup(DRAFT_FROM_PACKAGE[i].contactor, DRAFT_FROM_PACKAGE[i].title, DRAFT_FROM_PACKAGE[i].body, page_num);break;
        case 6: read_email_popup(DUSTBIN_FROM_PACKAGE[i].contactor, DUSTBIN_FROM_PACKAGE[i].title, DUSTBIN_FROM_PACKAGE[i].body, page_num);break;
    }
}

void reply_email(GtkButton* button, gpointer data){
    gtk_widget_destroy(GTK_WIDGET(data));
    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook),1);
}

void fresh_button(GtkButton* button, gpointer data){
    switch(page_num){
        case 2:gtk_container_remove(GTK_CONTAINER(table_inbox), scrolled_inbox);
            scrolled_inbox=get_scrolledwindow("Inbox");
            gtk_table_attach_defaults(GTK_TABLE(table_inbox), scrolled_inbox,0,5,1,7);break;
        case 3:gtk_container_remove(GTK_CONTAINER(table_contact), scrolled_contact);
            scrolled_contact=get_scrolledwindow("Contact");
            gtk_table_attach_defaults(GTK_TABLE(table_contact), scrolled_contact,0,5,1,7);break;
        case 4:gtk_container_remove(GTK_CONTAINER(table_sent), scrolled_sent);
            scrolled_sent=get_scrolledwindow("Sent");
            gtk_table_attach_defaults(GTK_TABLE(table_sent), scrolled_sent,0,5,1,7);break;
        case 5:gtk_container_remove(GTK_CONTAINER(table_draft), scrolled_draft);
            scrolled_draft=get_scrolledwindow("Draft");
            gtk_table_attach_defaults(GTK_TABLE(table_draft), scrolled_draft,0,5,1,7);break;
        case 6:gtk_container_remove(GTK_CONTAINER(table_dustbin), scrolled_dustbin);
            scrolled_dustbin=get_scrolledwindow("Dustbin");
            gtk_table_attach_defaults(GTK_TABLE(table_dustbin), scrolled_dustbin,0,5,1,7);break;
    }
    gtk_widget_show_all(window);
}

void add_contactor_button(GtkButton* button, gpointer data){
    GtkWidget* popup=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget* table=gtk_table_new(3,3,TRUE);
    GtkWidget* button_confirm=gtk_button_new_with_label("Confirm");
    GtkWidget* label_remark=gtk_label_new("Remark");
    GtkWidget* label_username=gtk_label_new("Username");

    entry_remark=gtk_entry_new(); entry_username=gtk_entry_new();

    gtk_container_add(GTK_CONTAINER(popup), table);
    gtk_table_attach_defaults(GTK_TABLE(table), label_remark, 0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table), label_username, 0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table), entry_remark, 1,3,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table), entry_username, 1,3,1,2);

    gtk_table_attach_defaults(GTK_TABLE(table), button_confirm, 1,2,2,3);

    g_signal_connect(button_confirm,"clicked",G_CALLBACK(add_contactor_confirm),popup);

    gtk_window_set_title(GTK_WINDOW(popup), "Add Contactor");
    gtk_widget_set_size_request(popup, 300,200);
    gtk_window_set_position(GTK_WINDOW(popup), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(popup), FALSE);
    gtk_widget_show_all(popup);

}

void add_contactor_confirm(GtkButton* button, gpointer data){

    char remark[100] = {'\0'};
    strcat(remark, gtk_entry_get_text(GTK_ENTRY(entry_remark)));
    char username[100] = {'\0'};
    strcat(username, gtk_entry_get_text(GTK_ENTRY(entry_username)));
    printf("%s\n%s\n", remark, username);
    gtk_widget_destroy(GTK_WIDGET(data));
    int flag = 1;
    if (ADD_CONTACT(remark, username)) {
        flag = 1;
    } else flag = 0;

    /*flag=connect */
    GtkWidget *popup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *label = gtk_label_new(flag ? "Add Success!" : "Add Failure");

    gtk_container_add(GTK_CONTAINER(popup), label);
    gtk_window_set_title(GTK_WINDOW(popup), "Information");
    gtk_widget_set_size_request(popup, 400, 300);
    gtk_window_set_position(GTK_WINDOW(popup), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(popup), FALSE);
    gtk_widget_show_all(popup);
}

void search_email_button(GtkButton* button, gpointer data){
    const char* title=gtk_entry_get_text(GTK_ENTRY(entry_search));
    printf("search title: %s\n",title);
    int flag=1,i=0;
    for(;i<size_inbox;i++){
        if(!strcmp(title, EMAIL_FROM_PACKAGE[i].title)){flag=0; break;}
    }

    if(flag) return;
    printf("flag: %d\n",flag);
    flag_search=i;
    open_email(NULL, NULL);
    flag_search=-1;
}

void clear_input(GtkButton* button, gpointer data){
    gtk_entry_set_text(GTK_ENTRY(entry_addressee), "");
    gtk_entry_set_text(GTK_ENTRY(entry_subject), "");
    GtkTextBuffer* buffer=gtk_text_buffer_new(NULL);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(textview), buffer);
}

///* add accessory (begin)*/
//void file_ok_sel(GtkWidget* w, GtkFileSelection *fs){
//	char path[20000];
//	memset(acc_body, 0, sizeof(acc_body));
//	printf("path: %s\n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)));
//	sprintf(path,"%s",gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)) );
//	freopen(path,"r",stdin);
//	while(~scanf("%s", path)){
//		strcat(acc_body, path);
//	}
//	printf("%s\n", acc_body);
//	fclose(stdin);
//	gtk_widget_destroy(GTK_WIDGET(fs));
//}
//void file_cancel_sel(GtkWidget* w, GtkFileSelection *fs){
//	gtk_widget_destroy(GTK_WIDGET(fs));
//}
//void add_accessory(GtkButton* button, gpointer data){
//	printf("Add accessory!");
//	GtkWidget *filew= gtk_file_selection_new("Accessory Selection");
//	g_signal_connect (GTK_OBJECT(filew), "destroy",G_CALLBACK (gtk_widget_destroy), NULL);
//	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(filew)->ok_button),"clicked",G_CALLBACK(file_ok_sel),filew);
//	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(filew)->cancel_button),"clicked",G_CALLBACK(file_cancel_sel),filew);
//	gtk_widget_show(filew);
//}
///* add accessory (end)*/

int main_mail(int argc, char *argv[]){
    gtk_init(&argc, &argv);

    notebook=init_notebook();

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Bit Email");
    gtk_widget_set_size_request(window, 1200,800);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(window),20);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add(GTK_CONTAINER(window), notebook);
    gtk_widget_show_all(window);
    gtk_main();
}


// judge_function_part
// ________________________________________

int judge(char *passwd, char *correct) {
    int flag1 = 0;
    int flag2 = 0;
    int len = strlen(passwd);
    if (len < 6 || len > 12)
        return 0;
    else {
        for (int i = 0; i < len; i++) {
            if (passwd[i] >= '0' && passwd[i] <= '9')
                flag1 = 1;
            if ((passwd[i] >= 'a' && passwd[i] <= 'z') || (passwd[i] >= 'A' && passwd[i] <= 'Z'))
                flag2 = 1;
        }
        if (flag1 * flag2 == 0)
            return 0;
        else {
            if (strcmp(passwd, correct) == 0)
                return 1;
            else
                return 0;
        }
    }
}

// login_function_part
// ________________________________________

void login_button_clicked(GtkWidget *widget, gpointer data) {

    Information *pRt = (Information *) data;
    //获取登录信息
    const gchar *a = gtk_entry_get_text(GTK_ENTRY(pRt->emailname));
    const gchar *b = gtk_entry_get_text(GTK_ENTRY(pRt->password));
    memset(LOGGER, '\0', sizeof(LOGGER));
    strcat(LOGGER, a);
    //check判断登录状况
    check(a, b);

    //printf("username:%s\n", a);
    //printf("password:%s\n", b);
    return;
}

void register_button_clicked(GtkWidget *widget, gpointer data) {
    register_main();
}

void forget_button_clicked(GtkWidget *widget, gpointer data) {
    Verification_window();
}

void remove_button_clicked(GtkWidget *widget, gpointer data) {
    Information *pRt = (Information *) data;
    //获取登录信息
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(pRt->emailname));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(pRt->password));
    //连接数据库，把登录信息传到数据库并比对，获得返回值
    //0弹窗+输入信息不在数据库中，1成功注销账户，else弹窗+系统出错
    /*int send=sendto_sql();//连接数据库
    if (send==0)
    {
        Fail_remove();//跳出后重新输入用户信息
    }
    if (send==1)
    {
        remove_success();
    }
    else System_false();
*/
    if (SIGN_WHOLE_PROCESS(username, password) && LOGOFF_DEACTIVIATE_ACCOUNT_BUTTON_CLICKED(username)) {
        remove_success();
    } else {
        Fail_remove();
    }
}

void main_window(GtkWidget *a) {

    gtk_widget_destroy(a);
    //初始化
    gtk_init(0, 0);
    //主窗口
    GtkWidget *window;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Flower Mailbox");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(window, 1500, 800);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable(window, FALSE);
    load_css();
    //字体大小
    PangoFontDescription *font1 = pango_font_description_from_string ("Sans");
    pango_font_description_set_size (font1, 20 * PANGO_SCALE);

    PangoFontDescription *font2 = pango_font_description_from_string ("Sans-serif");
    pango_font_description_set_size (font2, 60 * PANGO_SCALE);


    //确定各模块坐标
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    //大标题
    GtkWidget *label_main = gtk_label_new("WELCOME");
    gtk_fixed_put(GTK_FIXED(fixed), label_main, 450, 125);
    gtk_widget_modify_font(label_main, font2);

    //用户名
    GtkWidget *label_emailname = gtk_label_new("E-mail name");
    gtk_fixed_put(GTK_FIXED(fixed), label_emailname, 430, 350);

    GtkWidget *entry1 = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry1, 625, 350);
    gtk_widget_set_size_request(entry1, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry1), 100);
    Info.emailname = GTK_ENTRY(entry1);
    gtk_widget_modify_font(label_emailname, font1);

    //密码
    GtkWidget *label_password = gtk_label_new("Password");
    gtk_fixed_put(GTK_FIXED(fixed), label_password, 450, 455);

    GtkWidget *entry2 = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry2, 625, 450);
    gtk_widget_set_size_request(entry2, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry2), 15);
    Info.password = GTK_ENTRY(entry2);
    gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);
    gtk_widget_modify_font(label_password, font1);

    //登录按钮
    GtkWidget *login_button = gtk_button_new_with_label("Login");
    gtk_fixed_put(GTK_FIXED(fixed), login_button, 300, 600);
    gtk_widget_set_size_request(login_button, 400, 100);
    gtk_widget_modify_font(login_button, font1);

    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(login_button_clicked), (gpointer) &Info);

    //注册按钮
    GtkWidget *register_button = gtk_button_new_with_label("Register");
    gtk_fixed_put(GTK_FIXED(fixed), register_button, 800, 600);
    gtk_widget_set_size_request(register_button, 400, 100);
    gtk_widget_modify_font(register_button, font1);

    g_signal_connect(G_OBJECT(register_button), "clicked", G_CALLBACK(register_button_clicked), NULL);

    //忘记密码
    GtkWidget *forget_button = gtk_button_new_with_label("Forget password?");
    gtk_fixed_put(GTK_FIXED(fixed), forget_button, 300, 750);
    gtk_widget_set_size_request(forget_button, 400, 100);
    gtk_widget_modify_font(forget_button, font1);

    g_signal_connect(G_OBJECT(forget_button), "clicked", G_CALLBACK(forget_button_clicked), NULL);

    //注销账户
    GtkWidget *remove_button = gtk_button_new_with_label("Deactivate account");
    gtk_fixed_put(GTK_FIXED(fixed), remove_button, 800, 750);
    gtk_widget_set_size_request(remove_button, 400, 100);
    gtk_widget_modify_font(remove_button, font1);

    g_signal_connect(G_OBJECT(remove_button), "clicked", G_CALLBACK(remove_button_clicked), (gpointer) &Info);

    //显示所有窗口
    gtk_widget_show_all(window);
    gtk_main();
    return;
}

// loginFUNCTION_function_part
// ________________________________________


void ok_clicked(GtkWidget *a, gpointer *data) {
    gtk_widget_destroy(GTK_WIDGET(data));
}

GtkWidget *create_window() {
    GtkWidget *window;

    gtk_init(0,0);
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),600,100);
    gtk_window_set_title(GTK_WINDOW(window),"Flower Mailbox");

    return window;
}

void System_false()//系统出错
{
    GtkWidget *window_v=create_window();
    GtkWidget *vbox;//竖直容器
    GtkWidget *halign;//水平对齐容器

    vbox = gtk_vbox_new(FALSE,50);
    gtk_container_add(GTK_CONTAINER(window_v),vbox);

    GtkWidget *label_main = gtk_label_new("\n\n\n\n\nSystem is deserting...");
    // gtk_widget_modify_font(label_main,font1);
    GtkWidget *ok_button = gtk_button_new_with_label("Oh no");
    gtk_widget_set_size_request(ok_button,150,50);

    gtk_box_pack_start(GTK_BOX(vbox),label_main,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(ok_button),"clicked",G_CALLBACK(ok_clicked),(gpointer*)window_v);
    gtk_widget_show_all(window_v);
    gtk_main();
}

void Fail_login_1()//密码不合法
{
    GtkWidget *window_v=create_window();
    GtkWidget *vbox;//竖直容器

    vbox = gtk_vbox_new(FALSE,50);
    gtk_container_add(GTK_CONTAINER(window_v),vbox);

    GtkWidget *label_main = gtk_label_new("\n\n\nLogin failure.Password is illegal.\n\nPlease fill in the box again.");
    GtkWidget *ok_button = gtk_button_new_with_label("Oh no");
    gtk_widget_set_size_request(ok_button,150,50);
    //gtk_widget_modify_font(label_main,font1);

    gtk_box_pack_start(GTK_BOX(vbox),label_main,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(ok_button),"clicked",G_CALLBACK(ok_clicked),(gpointer*)window_v);
    gtk_widget_show_all(window_v);
    gtk_main();
}

void Fail_login_2()//用户名不存在
{
    GtkWidget *window_v=create_window();
    GtkWidget *vbox;//竖直容器

    vbox = gtk_vbox_new(FALSE,50);
    gtk_container_add(GTK_CONTAINER(window_v),vbox);

    GtkWidget *label_main = gtk_label_new("\n\n\nLogin failure.Password is illegal.\n\nPlease fill in the box again.");
    GtkWidget *ok_button = gtk_button_new_with_label("Oh no");
    gtk_widget_set_size_request(ok_button,150,50);
    //gtk_widget_modify_font(label_main,font1);

    gtk_box_pack_start(GTK_BOX(vbox),label_main,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(ok_button),"clicked",G_CALLBACK(ok_clicked),(gpointer*)window_v);
    gtk_widget_show_all(window_v);
    gtk_main();
}

void Fail_login_3()//密码不正确
{
    GtkWidget *window_v=create_window();
    GtkWidget *vbox;//竖直容器
    GtkWidget *halign;//水平对齐容器

    vbox = gtk_vbox_new(FALSE,50);
    gtk_container_add(GTK_CONTAINER(window_v),vbox);

    GtkWidget *label_main = gtk_label_new("\n\n\nLogin failure.\n\nPassword is incorrect.");
    GtkWidget *ok_button = gtk_button_new_with_label("So sad");
    gtk_widget_set_size_request(ok_button,150,50);
    //gtk_widget_modify_font(label_main,font1);

    gtk_box_pack_start(GTK_BOX(vbox),label_main,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(ok_button),"clicked",G_CALLBACK(ok_clicked),(gpointer*)window_v);
    gtk_widget_show_all(window_v);
    gtk_main();
}
void Fail_verification()//验证失败
{
    GtkWidget *window_v=create_window();
    GtkWidget *vbox;//竖直容器
    GtkWidget *halign;//水平对齐容器

    vbox = gtk_vbox_new(FALSE,50);
    gtk_container_add(GTK_CONTAINER(window_v),vbox);

    GtkWidget *label_main = gtk_label_new("\n\n\nVerification failure.\n\nPlease try again.");
    GtkWidget *ok_button = gtk_button_new_with_label("Fine");
    gtk_widget_set_size_request(ok_button,150,50);
    //gtk_widget_modify_font(label_main,font1);

    gtk_box_pack_start(GTK_BOX(vbox),label_main,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(ok_button),"clicked",G_CALLBACK(ok_clicked),(gpointer*)window_v);
    gtk_widget_show_all(window_v);
    gtk_main();
}
void Fail_reset()//重设密码失败
{
    GtkWidget *window_v=create_window();
    GtkWidget *vbox;//竖直容器
    GtkWidget *halign;//水平对齐容器

    vbox = gtk_vbox_new(FALSE,50);
    gtk_container_add(GTK_CONTAINER(window_v),vbox);

    GtkWidget *label_main = gtk_label_new("\n\n\nReset password failure.\n\nPlease fill in your infomation again.");
    GtkWidget *ok_button = gtk_button_new_with_label("OK");
    gtk_widget_set_size_request(ok_button,150,50);
    //  gtk_widget_modify_font(label_main,font1);

    gtk_box_pack_start(GTK_BOX(vbox),label_main,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(ok_button),"clicked",G_CALLBACK(ok_clicked),(gpointer*)window_v);
    gtk_widget_show_all(window_v);
    gtk_main();
}


void reset_password_success()//重设密码成功
{
    GtkWidget *window_v=create_window();
    GtkWidget *vbox;//竖直容器
    GtkWidget *halign;//水平对齐容器

    vbox = gtk_vbox_new(FALSE,50);
    gtk_container_add(GTK_CONTAINER(window_v),vbox);

    GtkWidget *label_main = gtk_label_new("\n\n\n\nCongratuliations,now you can login.");
    GtkWidget *ok_button = gtk_button_new_with_label("Login right now");
    gtk_widget_set_size_request(ok_button,150,50);
    //gtk_widget_modify_font(label_main,font1);

    gtk_box_pack_start(GTK_BOX(vbox),label_main,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(ok_button),"clicked",G_CALLBACK(ok_clicked),(gpointer*)window_v);
    gtk_widget_show_all(window_v);
    gtk_main();
}

void Fail_remove()//注销失败
{
    GtkWidget *window_v=create_window();
    GtkWidget *vbox;//竖直容器
    GtkWidget *halign;//水平对齐容器

    vbox = gtk_vbox_new(FALSE,50);
    gtk_container_add(GTK_CONTAINER(window_v),vbox);

    GtkWidget *label_main = gtk_label_new("\n\n\nRemove failure.\n\nPlease fill in your infomation again.");
    GtkWidget *ok_button = gtk_button_new_with_label("OK");
    gtk_widget_set_size_request(ok_button,150,50);
    //  gtk_widget_modify_font(label_main,font1);

    gtk_box_pack_start(GTK_BOX(vbox),label_main,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(ok_button),"clicked",G_CALLBACK(ok_clicked),(gpointer*)window_v);
    gtk_widget_show_all(window_v);
    gtk_main();
}

void remove_success()//注销成功
{
    GtkWidget *window_v=create_window();
    GtkWidget *vbox;//竖直容器
    GtkWidget *halign;//水平对齐容器

    vbox = gtk_vbox_new(FALSE,50);
    gtk_container_add(GTK_CONTAINER(window_v),vbox);

    GtkWidget *label_main = gtk_label_new("\n\n\n\nGood bye my friend~");
    GtkWidget *ok_button = gtk_button_new_with_label("See U");
    gtk_widget_set_size_request(ok_button,150,50);
    //  gtk_widget_modify_font(label_main,font1);

    gtk_box_pack_start(GTK_BOX(vbox),label_main,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(ok_button),"clicked",G_CALLBACK(ok_clicked),(gpointer*)window_v);
    gtk_widget_show_all(window_v);
    gtk_main();
}

// popup_part
// ________________________________________


void okclicked(GtkWidget *a, gpointer *data) {
    gtk_widget_destroy(GTK_WIDGET(data));
}

GtkWidget *createwindow() {
    GtkWidget *window;

    gtk_init(0,0);
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),600,100);
    gtk_window_set_title(GTK_WINDOW(window),"POPUP");

    return window;
}

void username_error()//用户名重复
{
    GtkWidget *window_v=createwindow();
    GtkWidget *vbox;

    vbox = gtk_vbox_new(FALSE,50);
    gtk_container_add(GTK_CONTAINER(window_v),vbox);


    GtkWidget *label_main = gtk_label_new("\n\n\n\nUsername Repeat!Please Change!");
    GtkWidget *ok_button = gtk_button_new_with_label("OK");
    gtk_widget_set_size_request(ok_button,150,50);


    gtk_box_pack_start(GTK_BOX(vbox),label_main,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(ok_button),"clicked",G_CALLBACK(okclicked),(gpointer*)window_v);
    gtk_widget_show_all(window_v);
    gtk_main();
}

void password_error()//密码不合法
{
    GtkWidget *window_v=createwindow();
    GtkWidget *vbox;//竖直容器

    vbox = gtk_vbox_new(FALSE,50);
    gtk_container_add(GTK_CONTAINER(window_v),vbox);

    GtkWidget *label_main = gtk_label_new("\n\n\n\nIncorrect Password Foramte!");
    GtkWidget *ok_button = gtk_button_new_with_label("OK");
    gtk_widget_set_size_request(ok_button,150,50);

    gtk_box_pack_start(GTK_BOX(vbox),label_main,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(ok_button),"clicked",G_CALLBACK(okclicked),(gpointer*)window_v);
    gtk_widget_show_all(window_v);
    gtk_main();
}

void register_success()//登录成功
{
    GtkWidget *window_v=createwindow();
    GtkWidget *vbox;//竖直容器

    vbox = gtk_vbox_new(FALSE,50);
    gtk_container_add(GTK_CONTAINER(window_v),vbox);

    GtkWidget *label_main = gtk_label_new("\n\n\n\nCongratulation Successful Registration!");
    GtkWidget *ok_button = gtk_button_new_with_label("OK");
    gtk_widget_set_size_request(ok_button,150,50);

    gtk_box_pack_start(GTK_BOX(vbox),label_main,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(ok_button),"clicked",G_CALLBACK(okclicked),(gpointer*)window_v);

    gtk_widget_show_all(window_v);
    gtk_main();
}


// registermain_part
// ________________________________________


Information Register;
GtkWidget *window;

void button_clicked(GtkWidget *widget, Information *a) {
    const gchar *ema;
    const gchar *pet;
    const gchar *pas;
    const gchar *con;
    const gchar *squ;
    const gchar *ans;
    const gchar *des;
    ema = gtk_entry_get_text(GTK_ENTRY(a->emailname));
    pet = gtk_entry_get_text(GTK_ENTRY(a->petname));
    pas = gtk_entry_get_text(GTK_ENTRY(a->password));
    con = gtk_entry_get_text(GTK_ENTRY(a->confirm));
    des = gtk_entry_get_text(GTK_ENTRY(a->description));
    squ = gtk_entry_get_text(GTK_ENTRY(a->security_question));
    ans = gtk_entry_get_text(GTK_ENTRY(a->answer));

    // printf("%s\n %s\n %s\n",use,pas,con);
    int jud = judge(pas, con);
    //printf("%d\n",jud);
    if (jud == 0) {
        password_error();
    } else {
        int res = flag_transmit(ema, pet, pas, des, squ, ans);
        if (res == 2)//用户名重复
        {
            username_error();
        } else if (res == 1)//注册成功
        {
            gtk_widget_destroy(window);//关闭注册窗口
            register_success();
        }
    }
}


int register_main() {
    //gtk环境初始化
    gtk_init(NULL,NULL);
    //创建一个窗口

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "mailbox register");
    //窗口在显示器中居中显示
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    //设置窗口大小
    gtk_window_set_default_size(GTK_WINDOW(window),1500,1100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_resizable(window, FALSE);

    //字体大小

    PangoFontDescription *font1 = pango_font_description_from_string ("Sans");
    pango_font_description_set_size (font1, 20 * PANGO_SCALE);

    PangoFontDescription *font2 = pango_font_description_from_string ("Roman");
    pango_font_description_set_size (font2, 80 * PANGO_SCALE);

    PangoFontDescription *font3 = pango_font_description_from_string ("Roman");
    pango_font_description_set_size (font3, 55 * PANGO_SCALE);

    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    //大标题
    GtkWidget *label_main=gtk_label_new("REGISTER");
    gtk_fixed_put(GTK_FIXED(fixed),label_main,620,15);
    gtk_widget_modify_font(label_main,font3);

    //邮箱名
    GtkWidget *entry_emailname= gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),entry_emailname,650,130);
    gtk_widget_set_size_request(entry_emailname,400,50);
    gtk_entry_set_max_length(GTK_ENTRY(entry_emailname),30);
    Register.emailname=GTK_ENTRY(entry_emailname);

    GtkWidget *label_emailname=gtk_label_new("E-mail name");
    gtk_fixed_put(GTK_FIXED(fixed),label_emailname,460,130);

    gtk_widget_modify_font(label_emailname,font1);

    //昵称
    GtkWidget *entry_username= gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),entry_username,650,230);
    gtk_widget_set_size_request(entry_username,400,50);
    gtk_entry_set_max_length(GTK_ENTRY(entry_username),20);
    Register.petname=GTK_ENTRY(entry_username);


    GtkWidget *label_username=gtk_label_new("Pet name");
    gtk_fixed_put(GTK_FIXED(fixed),label_username,475,230);

    gtk_widget_modify_font(label_username,font1);


    //密码
    GtkWidget *label1=gtk_label_new(" 6-12 digits ,letters and numbers only");
    gtk_fixed_put(GTK_FIXED(fixed),label1,650,310);
    //gtk_widget_modify_font(label1,font3);

    GtkWidget *entry_password= gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry_password,650,330);
    gtk_widget_set_size_request(entry_password,400,50);
    gtk_entry_set_max_length(GTK_ENTRY(entry_password),15);

    gtk_entry_set_visibility(GTK_ENTRY(entry_password),FALSE);
    Register.password=GTK_ENTRY(entry_password);

    GtkWidget *label_password=gtk_label_new("Password");
    gtk_fixed_put(GTK_FIXED(fixed),label_password,475,335);

    gtk_widget_modify_font(label_password,font1);

    //确认密码

    GtkWidget *entry_confirm= gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),entry_confirm,650,430);
    gtk_widget_set_size_request(entry_confirm,400,50);
    gtk_entry_set_max_length(GTK_ENTRY(entry_confirm),15);
    gtk_entry_set_visibility(GTK_ENTRY(entry_confirm),FALSE);
    Register.confirm=GTK_ENTRY(entry_confirm);



    GtkWidget *label_confirm=gtk_label_new("Confirm");
    gtk_fixed_put(GTK_FIXED(fixed),label_confirm,480,435);

    gtk_widget_modify_font(label_confirm,font1);

    //密保问题
    GtkWidget *entry_se_q= gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),entry_se_q,650,530);
    gtk_widget_set_size_request(entry_se_q,400,50);
    gtk_entry_set_max_length(GTK_ENTRY(entry_se_q),200);
    Register.security_question=GTK_ENTRY(entry_se_q);

    GtkWidget *label_se_q=gtk_label_new("Security Question");
    gtk_fixed_put(GTK_FIXED(fixed),label_se_q,400,535);

    gtk_widget_modify_font(label_se_q,font1);

    //答案设置
    GtkWidget *entry_answer= gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),entry_answer,650,630);
    gtk_widget_set_size_request(entry_answer,400,50);
    gtk_entry_set_max_length(GTK_ENTRY(entry_answer),15);
    Register.answer=GTK_ENTRY(entry_answer);

    GtkWidget *label_answer=gtk_label_new("Answer");
    gtk_fixed_put(GTK_FIXED(fixed),label_answer,480,635);

    gtk_widget_modify_font(label_answer,font1);

    //个性签名

    GtkWidget *entry_personal= gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),entry_personal,650,730);
    gtk_widget_set_size_request(entry_personal,400,50);
    gtk_entry_set_max_length(GTK_ENTRY(entry_personal),50);
    Register.description=GTK_ENTRY(entry_personal);

    GtkWidget *label_personal=gtk_label_new("Personal Signature");
    gtk_fixed_put(GTK_FIXED(fixed),label_personal,400,735);

    gtk_widget_modify_font(label_personal,font1);

    //立即注册按钮
    GtkWidget *button_register = gtk_button_new_with_label("Register Now");

    gtk_fixed_put(GTK_FIXED(fixed),button_register,450,850);
    gtk_widget_set_size_request(button_register,600,80);

//	gtk_widget_modify_font(button_register,font1);

    g_signal_connect(button_register, "clicked", G_CALLBACK(button_clicked),&Register);
    //显示所有窗口
    gtk_widget_show_all(window);

    //主事件循环
    gtk_main();
    return window;
}

// reset_password_part
// ________________________________________


void reset_judge(char *password, char *confirm, char *answer)//重设密码合法性判断
{
    int flag1 = 0;
    int flag2 = 0;
    int len = strlen(confirm);
    if (len < 6 || len > 12) Fail_login_1();
    else {
        for (int i = 0; i < len; i++) {
            if (confirm[i] >= '0' && confirm[i] <= '9')
                flag1 = 1;
            if ((confirm[i] >= 'a' && confirm[i] <= 'z') || (confirm[i] >= 'A' && confirm[i] <= 'Z'))
                flag2 = 1;
        }
        if (flag1 * flag2 == 0) Fail_login_1();
        else if (!strcmp(password, confirm)) Fail_login_1();
        else {
            //int reset=验证密保答案是否正确并传输新密码()； 0不正确 1正确
            if (RECOVERY_BUTTON_CLICKED_(answer, password) != false) Fail_reset();
            else {
                gtk_widget_destroy(window_r);
                reset_password_success();
            }
        }
    }
}

void update_button_clicked(GtkWidget *widget, gpointer data) {

    Information *aaa = (Information *) data;

    //获取登录信息
    const gchar *answer = gtk_entry_get_text(GTK_ENTRY(aaa->answer));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(aaa->password));
    const gchar *confirm = gtk_entry_get_text(GTK_ENTRY(aaa->confirm));
    reset_judge(password, confirm, answer);
}

int reset_password_window(char *ques)//重设密码窗口
{

    //创建重设密码窗口

    window_r=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window_r),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window_r),1500,1100);
    gtk_window_set_title(GTK_WINDOW(window_r), "Flower Mailbox");
    g_signal_connect_swapped(G_OBJECT(window_r),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    //字体大小
    PangoFontDescription *font1 = pango_font_description_from_string ("Sans");
    pango_font_description_set_size (font1, 20 * PANGO_SCALE);

    PangoFontDescription *font2 = pango_font_description_from_string ("Lucida Console");
    pango_font_description_set_size (font2, 60 * PANGO_SCALE);

    //确定各模块坐标
    GtkWidget *fixed = gtk_fixed_new();

    //大标题
    GtkWidget *label_main = gtk_label_new("Reset password");
    gtk_fixed_put(GTK_FIXED(fixed),label_main,275,125);
    gtk_widget_modify_font(label_main,font2);

//显示密保问题

    GtkWidget *label_ques=gtk_label_new("");
    gtk_label_set_text(label_ques,ques);
    gtk_fixed_put(GTK_FIXED(fixed),label_ques,400,400);
    gtk_widget_modify_font(label_ques,font1);

//输入密保答案
    GtkWidget *label_answer=gtk_label_new("Answer");
    gtk_fixed_put(GTK_FIXED(fixed),label_answer,440,500);

    GtkWidget *entry0= gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),entry0,625,500);
    gtk_widget_set_size_request(entry0,400,50);
    gtk_entry_set_max_length(GTK_ENTRY(entry0),20);
    aa.answer=GTK_ENTRY(entry0);

    gtk_widget_modify_font(label_answer,font1);

    ///////////////////////////////////////////输入新密码并确认
    //新密码
    GtkWidget *label_password_1=gtk_label_new("New password");
    gtk_fixed_put(GTK_FIXED(fixed),label_password_1,400,610);

    GtkWidget *entry1= gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),entry1,625,610);
    gtk_widget_set_size_request(entry1,400,50);
    gtk_entry_set_max_length(GTK_ENTRY(entry1),15);
    aa.password=GTK_ENTRY(entry1);

    gtk_entry_set_visibility(GTK_ENTRY(entry1),FALSE);
    gtk_widget_modify_font(label_password_1,font1);

    //确认密码
    GtkWidget *label_password_2 = gtk_label_new("Confirm");
    gtk_fixed_put(GTK_FIXED(fixed),label_password_2,430,720);

    GtkWidget *entry2 = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),entry2,625,720);
    gtk_widget_set_size_request(entry2,400,50);
    gtk_entry_set_max_length(GTK_ENTRY(entry2),15);
    aa.confirm= GTK_ENTRY(entry2);

    gtk_entry_set_visibility(GTK_ENTRY(entry2),FALSE);
    gtk_widget_modify_font(label_password_2,font1);

    //提交按钮
    GtkWidget *update_button= gtk_button_new_with_label("Submit");
    gtk_container_add(GTK_CONTAINER(window_r),fixed);
    gtk_fixed_put(GTK_FIXED(fixed),update_button,430,820);
    gtk_widget_set_size_request(update_button,600,100);
    gtk_widget_modify_font(update_button,font1);

    g_signal_connect(update_button,"clicked", G_CALLBACK(update_button_clicked),(gpointer)&aa);

    gtk_widget_show_all(window_r);
    gtk_main();
    return 0;
}

// socket_connection_part
// ________________________________________


void load_css(void) {
    GtkCssProvider *provider;
    GdkDisplay     *display;
    GdkScreen      *screen;
    /// ***
    const gchar *css_style_file = "../style.css";
    GFile *css_fp               = g_file_new_for_path (css_style_file );
    GError *error               = 0;
    /// ***
    provider = gtk_css_provider_new ();
    display  = gdk_display_get_default ();
    screen   = gdk_display_get_default_screen ( display );
    /// ***
    gtk_style_context_add_provider_for_screen   ( screen, GTK_STYLE_PROVIDER ( provider ), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION );
    gtk_css_provider_load_from_file             ( provider, css_fp, &error );
    /// ***
}

void socket_button_clicked(GtkWidget *widget, gpointer data) {
    if (CONNECTION()) {
        //int i=socket();0 false,1 true
        int i = 1;
        printf("CONNECT_EXPECTED_SUCCESS\n");
        main_window((GtkWidget *) data);
    } else {
        printf("CONNECTION FAILED\n");
    }
}



// verification_function_part
// ________________________________________

void submit_button_clicked(GtkWidget *widget, gpointer data) {

    Information *pRt = (Information *) data;
    //获取登录信息
    const gchar *account = gtk_entry_get_text(GTK_ENTRY(pRt->emailname));
    memset(LOGGER, '\0', sizeof(LOGGER));
    strcat(LOGGER, account);
    //const gchar *b = gtk_entry_get_text(GTK_ENTRY(pRt->security_question));
    //const gchar *c = gtk_entry_get_text(GTK_ENTRY(pRt->answer));
    //连接数据库 ,密保问题
    char ques[200] = {'\0'};
    if (GET_RECOVER_QUESTION(account, ques)) {
        gtk_widget_destroy(window_v); // 关闭验证窗口
        reset_password_window(ques); // 打开重设密码窗口
    }


}

int Verification_window() {//验证页面
    //窗口创建
    gtk_init(0, 0);
    window_v = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window_v), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window_v), 1500, 1100);
    gtk_window_set_title(GTK_WINDOW(window_v), "Flower Mailbox");
    g_signal_connect_swapped(G_OBJECT(window_v), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable(window_v, FALSE);
    //字体大小
    PangoFontDescription *font1 = pango_font_description_from_string("Sans");
    pango_font_description_set_size(font1,
                                    20 * PANGO_SCALE);

    PangoFontDescription *font2 = pango_font_description_from_string("Roman");
    pango_font_description_set_size(font2,
                                    90 * PANGO_SCALE);

    //确定各模块坐标
    GtkWidget *fixed = gtk_fixed_new();

    //大标题
    GtkWidget *label_main = gtk_label_new("Verification");
    gtk_fixed_put(GTK_FIXED(fixed), label_main, 450, 125);
    gtk_widget_modify_font(label_main, font2);

    //用户名
    GtkWidget *label_username=gtk_label_new("Email-name");
    gtk_fixed_put(GTK_FIXED(fixed),label_username,450,475);


    GtkWidget *entry1= gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),entry1,625,475);
    gtk_widget_set_size_request(entry1,400,50);
    gtk_entry_set_max_length(GTK_ENTRY(entry1),15);
    secure.emailname=GTK_ENTRY(entry1);
    gtk_widget_modify_font(label_username,font1);

    //提交按钮
    GtkWidget *submit_button = gtk_button_new_with_label("Submit");
    gtk_container_add(GTK_CONTAINER(window_v),fixed);
    gtk_fixed_put(GTK_FIXED(fixed),submit_button,450,700);
    gtk_widget_set_size_request(submit_button,600,100);
    gtk_widget_modify_font(submit_button,font1);

    g_signal_connect(submit_button,"clicked", G_CALLBACK(submit_button_clicked),&secure);


    gtk_widget_show_all(window_v);
    gtk_main();
    return 0;
}