#include "resetpassword.h"

void update_button_clicked(GtkWidget *widget, gpointer data)//这里数据传输有问题，无法获取
{
/*这里数据传输有问题，无法获取结构体里的数据 
	//判断密码是否合法
	//struct Un_sq * aaa= (struct Un_sq)data;
    //获取登录信息 
	const gchar *a = gtk_entry_get_text(GTK_ENTRY(aaa->pw));
	const gchar *b = gtk_entry_get_text(GTK_ENTRY(aaa->new_pw));
	judge(a,b);
*/
}

int reset_password_window(struct Un_sq *ss)//重设密码窗口 
{

    printf("%s\n", gtk_entry_get_text(GTK_ENTRY(ss->un)));
    //创建重设密码窗口
    GtkWidget *window_r;
    window_r = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window_r), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window_r), 1500, 1100);
    gtk_window_set_title(GTK_WINDOW(window_r), "Flower Mailbox");
    g_signal_connect_swapped(G_OBJECT(window_r), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //字体大小
    PangoFontDescription *font1 = pango_font_description_from_string("Sans");
    pango_font_description_set_size(font1, 20 * PANGO_SCALE);

    PangoFontDescription *font2 = pango_font_description_from_string("Lucida Console");
    pango_font_description_set_size(font2, 90 * PANGO_SCALE);

    //确定各模块坐标 
    GtkWidget *fixed = gtk_fixed_new();

    //大标题
    GtkWidget *label_main = gtk_label_new("Reset password");
    gtk_fixed_put(GTK_FIXED(fixed), label_main, 275, 125);
    gtk_widget_modify_font(label_main, font2);

    ///////////////////////////////////////////输入新密码并确认
    //新密码
    GtkWidget *label_password_1 = gtk_label_new("New password");
    gtk_fixed_put(GTK_FIXED(fixed), label_password_1, 400, 400);

    GtkWidget *entry1 = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry1, 625, 400);
    gtk_widget_set_size_request(entry1, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry1), 15);
    ss->pw = GTK_ENTRY(entry1);

    gtk_entry_set_visibility(GTK_ENTRY(entry1), FALSE);
    gtk_widget_modify_font(label_password_1, font1);

    //确认密码
    GtkWidget *label_password_2 = gtk_label_new("Confirm");
    gtk_fixed_put(GTK_FIXED(fixed), label_password_2, 430, 510);

    GtkWidget *entry2 = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry2, 625, 510);
    gtk_widget_set_size_request(entry2, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry2), 15);
    ss->pw = GTK_ENTRY(entry2);

    gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);
    gtk_widget_modify_font(label_password_2, font1);

    //提交按钮
    GtkWidget *update_button = gtk_button_new_with_label("Submit");
    gtk_container_add(GTK_CONTAINER(window_r), fixed);
    gtk_fixed_put(GTK_FIXED(fixed), update_button, 500, 700);
    gtk_widget_set_size_request(update_button, 500, 100);
    gtk_widget_modify_font(update_button, font1);

    g_signal_connect(update_button, "clicked", G_CALLBACK(update_button_clicked), (gpointer) ss);

    gtk_widget_show_all(window_r);
    gtk_main();
    return 0;
}
