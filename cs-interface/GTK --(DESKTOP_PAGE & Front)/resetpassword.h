//
// Created by guangtao on 2020/9/13.
//

#ifndef FACE_RESETPASSWORD_H
#define FACE_RESETPASSWORD_H

#include<gtk/gtk.h>
#include<pango/pango.h>

struct Un_sq {
    GtkEntry *un;
    GtkEntry *pw;
    GtkEntry *new_pw;
    GtkEntry *ques;
    GtkEntry *ans;
};

extern void update_button_clicked(GtkWidget *widget, gpointer data);

extern int reset_password_window(struct Un_sq *ss);


#endif //FACE_RESETPASSWORD_H
