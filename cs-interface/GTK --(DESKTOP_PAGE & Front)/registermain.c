#include "registermain.h"

/*void load_css ( void )
{
    GtkCssProvider *provider;
    GdkDisplay     *display;
    GdkScreen      *screen;
    /// ***
    const gchar *css_style_file = "style.css";
    GFile *css_fp               = g_file_new_for_path ( css_style_file );
    GError *error               = 0;
    /// ***
    provider = gtk_css_provider_new ();
    display  = gdk_display_get_default ();
    screen   = gdk_display_get_default_screen ( display );
    /// ***
    gtk_style_context_add_provider_for_screen   ( screen, GTK_STYLE_PROVIDER ( provider ), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION );
    gtk_css_provider_load_from_file             ( provider, css_fp, &error );
    /// ***
}*/


void button_clicked(GtkWidget *widget, REgister *a) {
    const gchar *use;
    const gchar *pas;
    const gchar *con;
    const gchar *squ;
    const gchar *ans;

    use = gtk_entry_get_text(GTK_ENTRY(a->username));
    pas = gtk_entry_get_text(GTK_ENTRY(a->password));
    con = gtk_entry_get_text(GTK_ENTRY(a->confirm));
    squ = gtk_entry_get_text(GTK_ENTRY(a->security_question));
    ans = gtk_entry_get_text(GTK_ENTRY(a->answer));


    // printf("%s\n %s\n %s\n",use,pas,con);
    int jud = judge(pas, con);
    int flag_transmit = -1;// 传递
    //printf("%d\n",jud);
    if (jud == 0) {
        password_error();
    } else {
        if (flag_transmit == 0)//用户名重复
        {
            username_error();
        } else if (flag_transmit == 1)//注册成功
        {
            /////
            register_success();
        }

    }
    return;
}


GtkWidget *register_main() {
    //gtk环境初始化
    gtk_init(NULL, NULL);
    //创建一个窗口
    load_css();
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "mailbox register");
    //窗口在显示器中居中显示
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    //设置窗口大小
    gtk_window_set_default_size(GTK_WINDOW(window), 1500, 1100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_resizable(window, FALSE);

    //字体大小	

    PangoFontDescription *font1 = pango_font_description_from_string("Sans");
    pango_font_description_set_size(font1, 20 * PANGO_SCALE);

    PangoFontDescription *font2 = pango_font_description_from_string("Lucida Console");
    pango_font_description_set_size(font2, 90 * PANGO_SCALE);

    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    //大标题
    GtkWidget *label_main = gtk_label_new("REGISTER");
    gtk_fixed_put(GTK_FIXED(fixed), label_main, 450, 125);
    gtk_widget_modify_font(label_main, font2);


    //用户名
    GtkWidget *entry_username = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry_username, 650, 350);
    gtk_widget_set_size_request(entry_username, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry_username), 20);
    Register.username = GTK_ENTRY(entry_username);


    GtkWidget *label_username = gtk_label_new("Username");
    gtk_fixed_put(GTK_FIXED(fixed), label_username, 475, 350);

    gtk_widget_modify_font(label_username, font1);


    //密码
    GtkWidget *label1 = gtk_label_new("be 6-12 digits long and contain letters and numbers");
    gtk_fixed_put(GTK_FIXED(fixed), label1, 650, 430);
    //gtk_widget_modify_font(label1,font3);

    GtkWidget *entry_password = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry_password, 650, 450);
    gtk_widget_set_size_request(entry_password, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry_password), 15);

    gtk_entry_set_visibility(GTK_ENTRY(entry_password), FALSE);
    Register.password = GTK_ENTRY(entry_password);

    GtkWidget *label_password = gtk_label_new("Password");
    gtk_fixed_put(GTK_FIXED(fixed), label_password, 475, 455);

    gtk_widget_modify_font(label_password, font1);

    //确认密码
    GtkWidget *label2 = gtk_label_new("please enter the password again");
    gtk_fixed_put(GTK_FIXED(fixed), label2, 650, 530);
    //   gtk_widget_modify_font(label2,font3);

    GtkWidget *entry_confirm = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry_confirm, 650, 550);
    gtk_widget_set_size_request(entry_confirm, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry_confirm), 15);
    gtk_entry_set_visibility(GTK_ENTRY(entry_confirm), FALSE);
    Register.confirm = GTK_ENTRY(entry_confirm);


    GtkWidget *label_confirm = gtk_label_new("Confirm");
    gtk_fixed_put(GTK_FIXED(fixed), label_confirm, 480, 555);

    gtk_widget_modify_font(label_confirm, font1);

    //密保问题
    GtkWidget *entry_se_q = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry_se_q, 650, 650);
    gtk_widget_set_size_request(entry_se_q, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry_se_q), 200);
    Register.security_question = GTK_ENTRY(entry_se_q);

    GtkWidget *label_se_q = gtk_label_new("Security Question");
    gtk_fixed_put(GTK_FIXED(fixed), label_se_q, 400, 655);

    gtk_widget_modify_font(label_se_q, font1);

    //答案设置
    GtkWidget *entry_answer = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry_answer, 650, 750);
    gtk_widget_set_size_request(entry_answer, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry_answer), 15);
    Register.answer = GTK_ENTRY(entry_answer);

    GtkWidget *label_answer = gtk_label_new("Answer");
    gtk_fixed_put(GTK_FIXED(fixed), label_answer, 480, 755);

    gtk_widget_modify_font(label_answer, font1);

    //立即注册按钮
    GtkWidget *button_register = gtk_button_new_with_label("Register Now");

    gtk_fixed_put(GTK_FIXED(fixed), button_register, 450, 900);
    gtk_widget_set_size_request(button_register, 600, 100);

//	gtk_widget_modify_font(button_register,font1);

    g_signal_connect(button_register, "clicked", G_CALLBACK(button_clicked), &Register);
    //显示所有窗口
    gtk_widget_show_all(window);

    //主事件循环
    gtk_main();
    return window;
}


