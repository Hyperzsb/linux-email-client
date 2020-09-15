//
// Created by guangtao on 2020/9/13.
//

#ifndef FACE_POPUP_H
#define FACE_POPUP_H

#include<gtk/gtk.h>

extern void okclicked(GtkWidget *a, gpointer *data);

extern GtkWidget *createwindow();

extern void username_error();

extern void password_error();

extern void register_success();

#endif //FACE_POPUP_H
