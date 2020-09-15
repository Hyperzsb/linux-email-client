#include "loginFunction.h"

void ok_clicked(GtkWidget *a, gpointer *data) {
    gtk_widget_destroy(GTK_WIDGET(data));
}

GtkWidget *create_window() {
    GtkWidget *window;

    gtk_init(0, 0);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect_swapped(G_OBJECT(window), "destroy",
                             G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 450, 300);
    gtk_window_set_title(GTK_WINDOW(window), "Error");

    return window;
}

void System_false()//系统出错
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING,
                                    GTK_BUTTONS_OK,
                                    "System is deserting...");
    gtk_window_set_title(GTK_WINDOW(dialog), "Error");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void Fail_login_1()//密码不合法
{
    GtkWidget *window_v = create_window();
    GtkWidget *vbox;//竖直容器 
    GtkWidget *halign;//水平对齐容器 

    vbox = gtk_vbox_new(FALSE, 50);
    gtk_container_add(GTK_CONTAINER(window_v), vbox);

    GtkWidget *label_main = gtk_label_new(
            "\n\n\n\n\nLogin failure.Password is illegal.\n\n\nPlease fill in the box again.\n");
    GtkWidget *ok_button = gtk_button_new_with_label("OK");
    gtk_widget_set_size_request(ok_button, 150, 50);

    gtk_box_pack_start(GTK_BOX(vbox), label_main, FALSE, FALSE, 10);
    halign = gtk_alignment_new(0.9, 0.1, 0, 0);
    gtk_container_add(GTK_CONTAINER(vbox), halign);
    gtk_container_add(GTK_CONTAINER(halign), ok_button);

    g_signal_connect(G_OBJECT(ok_button), "clicked",
                     G_CALLBACK(ok_clicked), (gpointer *) window_v);
    gtk_widget_show_all(window_v);
    gtk_main();
}

void Fail_login_2()//用户名不存在
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING,
                                    GTK_BUTTONS_OK,
                                    "Login failure.Username does not exist.");
    gtk_window_set_title(GTK_WINDOW(dialog), "Error");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void Fail_login_3()//密码不正确 
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING,
                                    GTK_BUTTONS_OK,
                                    "Login failure.Password is incorrect.");
    gtk_window_set_title(GTK_WINDOW(dialog), "Error");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void Fail_verification()//验证失败
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING,
                                    GTK_BUTTONS_OK,
                                    "Verification failure.Please try again.");
    gtk_window_set_title(GTK_WINDOW(dialog), "Error");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void reset_password_success()//重设密码成功 
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "Congratuliations,now you can login.");
    gtk_window_set_title(GTK_WINDOW(dialog), "Good");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void Fail_remove()//注销失败
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING,
                                    GTK_BUTTONS_OK,
                                    "Remove failure.Please fill in your infomation again.");
    gtk_window_set_title(GTK_WINDOW(dialog), "Error");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void remove_success()//注销成功
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "Good bye my friend~");
    gtk_window_set_title(GTK_WINDOW(dialog), "Bye bye");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
