//
// Created by guangtao on 2020/9/13.
//

#ifndef FACE_LOGIN_H
#define FACE_LOGIN_H

#include "verification.h"
#include <gtk/gtk.h>
#include <pango/pango.h>
#include "check.h"
#include "registermain.h"

struct Un_pw {
    GtkEntry *un;
    GtkEntry *pw;
};
extern struct Un_pw Info;//储存用户信息的结构

extern void login_button_clicked(GtkWidget *widget, gpointer data);

extern void register_button_clicked(GtkWidget *widget, gpointer data);

extern void forget_button_clicked(GtkWidget *widget, gpointer data);

extern void remove_button_clicked(GtkWidget *widget, gpointer data);

extern void load_css(void);


#endif //FACE_LOGIN_H
