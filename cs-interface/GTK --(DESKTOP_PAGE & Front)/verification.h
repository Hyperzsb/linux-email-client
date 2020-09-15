//
// Created by guangtao on 2020/9/13.
//

#ifndef FACE_VERIFICATION_H
#define FACE_VERIFICATION_H

#include <gtk/gtk.h>
#include <pango/pango.h>
#include "resetpassword.h"

extern struct Un_sq secure;//储存用户信息的结构

static GtkWidget *entry1;//输入行1，用户名
static GtkWidget *entry2;//输入行2，密保问题
static GtkWidget *entry3;//输入行3，密报答案

extern int Verification_window();

extern void submit_button_clicked(GtkWidget *widget, gpointer data);


#endif //FACE_VERIFICATION_H
