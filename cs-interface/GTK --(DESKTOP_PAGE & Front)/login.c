#include "login.h"

void login_button_clicked(GtkWidget *widget, gpointer data) {

    struct Un_pw *pRt = (struct Un_pw *) data;
    //获取登录信息 
    const gchar *a = gtk_entry_get_text(GTK_ENTRY(pRt->un));
    const gchar *b = gtk_entry_get_text(GTK_ENTRY(pRt->pw));
    //check判断登录状况
    check(a, b);
    //printf("username:%s\n", a);
    //printf("password:%s\n", b);
    return;
}

void register_button_clicked(GtkWidget *widget, gpointer data) {
    register_main();
}

void forget_button_clicked(GtkWidget *widget, gpointer data) {
    Verification_window();
}

void remove_button_clicked(GtkWidget *widget, gpointer data) {
    struct Un_pw *pRt = (struct Un_pw *) data;
    //获取登录信息 
    const gchar *a = gtk_entry_get_text(GTK_ENTRY(pRt->un));
    const gchar *b = gtk_entry_get_text(GTK_ENTRY(pRt->pw));
    //连接数据库，把登录信息传到数据库并比对，获得返回值
    //0弹窗+输入信息不在数据库中，1成功注销账户，else弹窗+系统出错
    /*int send=sendto_sql();//连接数据库
    if (send==0)
    {
        Fail_remove();//跳出后重新输入用户信息
    }
    if (send==1)
    {
        remove_success();
    }
    else System_false();
*/
    return;
}

void load_css(void) {
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    /// ***
    const gchar *css_style_file = "style.css";
    GFile *css_fp = g_file_new_for_path(css_style_file);
    GError *error = 0;
    /// ***
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    /// ***
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider, css_fp, &error);
    /// ***
}

static GtkWidget *entry1;//输入行1，用户名
static GtkWidget *entry2;//输入行2，密码

int main(int argc, char *argv[]) {
    //初始化
    gtk_init(&argc, &argv);
    //主窗口
    GtkWidget *window;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Flower Mailbox");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1500, 1100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable(window, FALSE);
    load_css();
    //字体大小
    PangoFontDescription *font1 = pango_font_description_from_string("Sans");
    pango_font_description_set_size(font1, 20 * PANGO_SCALE);

    PangoFontDescription *font2 = pango_font_description_from_string("Roman");
    pango_font_description_set_size(font2, 90 * PANGO_SCALE);



    //确定各模块坐标
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    //大标题
    GtkWidget *label_main = gtk_label_new("WELCOME");
    gtk_fixed_put(GTK_FIXED(fixed), label_main, 450, 125);
    gtk_widget_modify_font(label_main, font2);

    //用户名
    GtkWidget *label_username = gtk_label_new("Username");
    gtk_fixed_put(GTK_FIXED(fixed), label_username, 450, 350);

    GtkWidget *entry1 = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry1, 625, 350);
    gtk_widget_set_size_request(entry1, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry1), 20);
    Info.un = GTK_ENTRY(entry1);
    gtk_widget_modify_font(label_username, font1);

    //密码
    GtkWidget *label_password = gtk_label_new("Password");
    gtk_fixed_put(GTK_FIXED(fixed), label_password, 450, 455);

    GtkWidget *entry2 = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry2, 625, 450);
    gtk_widget_set_size_request(entry2, 400, 50);
    gtk_entry_set_max_length(GTK_ENTRY(entry2), 15);
    Info.pw = GTK_ENTRY(entry2);
    gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);
    gtk_widget_modify_font(label_password, font1);

    //登录按钮 
    GtkWidget *login_button = gtk_button_new_with_label("Login");
    gtk_fixed_put(GTK_FIXED(fixed), login_button, 300, 600);
    gtk_widget_set_size_request(login_button, 400, 100);
    gtk_widget_modify_font(login_button, font1);

    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(login_button_clicked), (gpointer) &Info);

    //注册按钮
    GtkWidget *register_button = gtk_button_new_with_label("Register");
    gtk_fixed_put(GTK_FIXED(fixed), register_button, 800, 600);
    gtk_widget_set_size_request(register_button, 400, 100);
    gtk_widget_modify_font(register_button, font1);

    g_signal_connect(G_OBJECT(register_button), "clicked", G_CALLBACK(register_button_clicked), NULL);

    //忘记密码 
    GtkWidget *forget_button = gtk_button_new_with_label("Forget password?");
    gtk_fixed_put(GTK_FIXED(fixed), forget_button, 300, 750);
    gtk_widget_set_size_request(forget_button, 400, 100);
    gtk_widget_modify_font(forget_button, font1);

    g_signal_connect(G_OBJECT(forget_button), "clicked", G_CALLBACK(forget_button_clicked), NULL);

    //注销账户
    GtkWidget *remove_button = gtk_button_new_with_label("Deactivate account");
    gtk_fixed_put(GTK_FIXED(fixed), remove_button, 800, 750);
    gtk_widget_set_size_request(remove_button, 400, 100);
    gtk_widget_modify_font(remove_button, font1);

    g_signal_connect(G_OBJECT(remove_button), "clicked", G_CALLBACK(remove_button_clicked), (gpointer) &Info);

    //显示所有窗口
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
