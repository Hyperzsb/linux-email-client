//
// Created by guangtao on 2020/9/13.
//

#ifndef FACE_LOGINFUNCTION_H
#define FACE_LOGINFUNCTION_H

#include <gtk/gtk.h>
#include <pango/pango.h>
#include <string.h>

extern void ok_clicked(GtkWidget *a, gpointer *data);

extern GtkWidget *create_window();

extern void System_false();

extern void Fail_login_1();

extern void Fail_login_2();

extern void Fail_login_3();

extern void Fail_verification();

extern void reset_password_success();

extern void Fail_remove();

extern void remove_success();


#endif //FACE_LOGINFUNCTION_H
