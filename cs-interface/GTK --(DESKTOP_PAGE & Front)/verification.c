#include "verification.h"

GtkWidget *window_v;//创建验证窗口指针

void submit_button_clicked(GtkWidget *widget, gpointer data) {

    struct Un_sq *pRt = (struct Un_sq *) data;
    //获取登录信息 
    const gchar *a = gtk_entry_get_text(GTK_ENTRY(pRt->un));
    const gchar *b = gtk_entry_get_text(GTK_ENTRY(pRt->ques));
    const gchar *c = gtk_entry_get_text(GTK_ENTRY(pRt->ans));
    //连接数据库  0验证失败，1验证成功
    /*int count=
    if (count==0)
    {
        Fail_verification();
    }*/
    int count = 1;
    if (count == 1) {
        gtk_widget_hide(window_v);//隐藏验证窗口
        reset_password_window(data);

    }/*
    else System_false(); 
*/
    // return;
}

int Verification_window()//验证页面 
{

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
    pango_font_description_set_size(font1, 20 * PANGO_SCALE);

    PangoFontDescription *font2 = pango_font_description_from_string("Lucida Console");
    pango_font_description_set_size(font2, 90 * PANGO_SCALE);

    //确定各模块坐标 
    GtkWidget *fixed = gtk_fixed_new();

    //大标题
    GtkWidget *label_main = gtk_label_new("Verification");
    gtk_fixed_put(GTK_FIXED(fixed), label_main, 450, 125);
    gtk_widget_modify_font(label_main, font2);

    //用户名
    GtkWidget *label_username = gtk_label_new("Username");
    gtk_fixed_put(GTK_FIXED(fixed), label_username, 450, 350);

    GtkWidget *entry1 = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry1, 625, 350);
    gtk_widget_set_size_request(entry1, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry1), 15);
    secure.un = GTK_ENTRY(entry1);
    //g_signal_connect(entry1,"activate", G_CALLBACK(username_callback),entry1);
    gtk_widget_modify_font(label_username, font1);

    //密保问题
    GtkWidget *label_ques = gtk_label_new("Security question");
    gtk_fixed_put(GTK_FIXED(fixed), label_ques, 390, 450);

    GtkWidget *entry2 = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry2, 625, 450);
    gtk_widget_set_size_request(entry2, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry2), 200);
    secure.ques = GTK_ENTRY(entry2);
    //g_signal_connect(entry2,"activate", G_CALLBACK(trans_password), entry2);
    gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);
    gtk_widget_modify_font(label_ques, font1);

    //密保答案
    GtkWidget *label_ans = gtk_label_new("Answer");
    gtk_fixed_put(GTK_FIXED(fixed), label_ans, 470, 555);

    GtkWidget *entry3 = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry3, 625, 550);
    gtk_widget_set_size_request(entry3, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry3), 200);
    secure.ans = GTK_ENTRY(entry3);
    //g_signal_connect(entry1,"activate", G_CALLBACK(username_callback),entry1);
    gtk_widget_modify_font(label_ans, font1);

    //提交按钮
    GtkWidget *submit_button = gtk_button_new_with_label("Submit");
    gtk_container_add(GTK_CONTAINER(window_v), fixed);
    gtk_fixed_put(GTK_FIXED(fixed), submit_button, 550, 700);
    gtk_widget_set_size_request(submit_button, 500, 100);
    gtk_widget_modify_font(submit_button, font1);

    g_signal_connect(submit_button, "clicked", G_CALLBACK(submit_button_clicked), &secure);


    gtk_widget_show_all(window_v);
    gtk_main();
    return 0;
}
