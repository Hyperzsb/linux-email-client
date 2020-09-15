//
// Created by guangtao on 2020/9/13.
//

#ifndef FACE_REGISTERMAIN_H
#define FACE_REGISTERMAIN_H

#include <gtk/gtk.h>
#include <pango/pango.h>
#include <stdio.h>
#include <string.h>
#include "popup.h"
#include "judge.h"
#include "login.h"

typedef struct {
    GtkWidget *username;//用户名
    GtkWidget *password;//密码
    GtkWidget *confirm;//密码确认
    GtkWidget *security_question;//密保问题
    GtkWidget *answer;//问题答案
} REgister;
extern REgister Register;

extern GtkWidget *register_main();

extern void button_clicked(GtkWidget *widget, REgister *a);


#endif //FACE_REGISTERMAIN_H
