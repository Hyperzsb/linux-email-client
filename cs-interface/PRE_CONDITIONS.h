//
// Created by guangtao on 2020/9/13.
//

#ifndef CLIENT_NEW_PRE_CONDITIONS_H
#define CLIENT_NEW_PRE_CONDITIONS_H

#define bool int
#define true 1
#define false 0

#define PASSWORD_LENGTH 50
#define USERNAME_LENGTH 50
#define SEQ_QUESTION_LENGTH 50
#define SEQ_QUANSWER_LENGTH 50
#define NICKNAME_LENGTH 50
#define DESCRIPTION_LENGTH 200

#include <cJSON.h>
#include <stdio.h>
#include "../loginFunction.h"
#include "../login.h"
#include "judge.h"
#include "FETCH_MAIL.h"
#include "cJSON_PACKAGES.h"
#include "check.h"
#include "info-acc.h"
#include "popup.h"
#include "registermain.h"
#include "resetpassword.h"
#include "verification.h"

#define COMMAND_LOGIN "login"
#define COMMAND_FRIEND "friend"
#define COMMAND_DELETE "delete"
#define COMMAND_DRAFT "draft_box"
#define COMMAND_SEND_M "send_mail"
#define COMMAND_RECOVER "recovery"
#define COMMAND_REGISTER "register"
#define COMMAND_RECV_M "receive_mail"

#define MAIL_TITLE_LENGTH_MAXIME 40

#define Q_A "请问您父亲的名字是？"
#define Q_B "请问您母亲的老家是？"
#define Q_C "请问您最喜欢的一道菜是？"
#define Q_D "请问您开始读大学时的年龄是？"
#define Q_E "请问您的生日是？xxxx-xx-xx"

#endif //CLIENT_NEW_PRE_CONDITIONS_H
