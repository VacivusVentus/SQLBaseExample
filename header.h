#ifndef HEADER_H
#define HEADER_H
#include <QString>
#include <QByteArray>
#include <QTranslator>

enum DBOperation {CONNECT = 0x0000, CLOSECONNECT = 0x0001, GET_TASKS = 0x0002, TASK_LINE = 0x0003, NORE = 0xFFFFFFFF,
                  ADD_TASK = 0x0004, USER_LINE = 0x0005, ADD_USER = 0x0006, TASK_USER_LINE = 0x0007,
                  UPDATE_TASK = 0x0008, UPDATE_USER_TASK = 0x0009, UPDATE_REPORT = 0x000A};

enum DBCause {COMPLETE = 0x0000, BAD_PACKAGE = 0x0001, ERR_USER = 0x0002, ERR_TASK = 0x0003, LOGIN_PASSWORD = 0x0004};

inline char *getMH()
{
    return (char *)"A5<<PACKAGE>>5A"; // Проверочные символы для проверки на смещение байт в пакете
}
//********************************************************************************
struct DBDisconnect {
    DBOperation operation;
    DBCause dbcause;
    DBDisconnect()
    {
        operation = DBOperation::CLOSECONNECT;
    }
    void toBytes(QByteArray &bArray)
    {
        bArray.clear();
        char *magicHead = getMH();
        bArray.append(magicHead, strlen(magicHead));
        unsigned int op = operation;
        bArray.append((char*)&op, 4);

        op = dbcause;
        bArray.append((char*)&op, 4);
    }
    QString getCauseToClose()
    {
        if (dbcause == DBCause::COMPLETE) return QTranslator::tr("Complete operation");
        if (dbcause == DBCause::BAD_PACKAGE) return QTranslator::tr("Bad package");
        if (dbcause == DBCause::ERR_USER) return QTranslator::tr("Couldn't find the user");
        if (dbcause == DBCause::ERR_TASK) return QTranslator::tr("Couldn't find the task");
        return QTranslator::tr("Unknown");
    }

    DBDisconnect(QByteArray &ba)
    {
        operation = DBOperation::CLOSECONNECT;
        char *magicHead = getMH();
        quint32 dpos = strlen(magicHead) + 4;
        char *data = &(ba.data())[dpos];
        dbcause = DBCause(*((int*)&data));
    }
};
//********************************************************************************
struct DBConnect{
    DBOperation operation;
    QString login;
    QString password;
    DBConnect()
    {
        operation = DBOperation::CONNECT;
    }
    void toBytes(QByteArray &bArray)
    {
        bArray.clear();
        char *magicHead = getMH();
        bArray.append(magicHead, strlen(magicHead));
        unsigned int op = operation;
        bArray.append((char*)&op, 4);
        QByteArray sbytes = login.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);
        sbytes = password.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);
    }

    DBConnect(QByteArray &ba)
    {
        operation = DBOperation::CONNECT;
        char *magicHead = getMH();
        quint32 dpos = strlen(magicHead) + 4;
        char *data = &(ba.data())[dpos];
        dpos = 4;
        quint32 op = *(data);
        QByteArray part;
        part.clear();
        part.append(&data[dpos], op);
        login = QString::fromUtf8(part);
        dpos += op;
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        password = QString::fromUtf8(part);
    }
};
//********************************************************************************
struct TaskInformation {
    DBOperation operation;
    QString task;
    QString descibe;
    QString startDate, endDate;
    quint8 progress;
    TaskInformation()
    {
        operation = DBOperation::TASK_LINE;
    }
    void toBytes(QByteArray &bArray)
    {
        bArray.clear();
        char *magicHead = getMH();
        bArray.append(magicHead, strlen(magicHead));
        unsigned int op = operation;
        bArray.append((char*)&op, 4);

        QByteArray sbytes = task.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = descibe.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = startDate.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = endDate.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        bArray.append((char)progress);
    }
    TaskInformation(QByteArray &ba)
    {
        operation = DBOperation::TASK_LINE;
        char *magicHead = getMH();
        quint32 dpos = strlen(magicHead) + 4;
        char *data = &(ba.data())[dpos];
        dpos = 4;
        quint32 op = *(data);
        QByteArray part;
        part.clear();
        part.append(&data[dpos], op);
        task = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        descibe = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        startDate = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        endDate = QString::fromUtf8(part);
        dpos += op;

        progress = *((quint8*)&data[dpos]);
    }
};
//********************************************************************************
struct UserInformation {
    DBOperation operation;
    QString fio;
    QString login;
    QString persontask;
    QString report;
    UserInformation()
    {
        operation = DBOperation::USER_LINE;
    }
    void toBytes(QByteArray &bArray)
    {
        bArray.clear();
        char *magicHead = getMH();
        bArray.append(magicHead, strlen(magicHead));
        unsigned int op = operation;
        bArray.append((char*)&op, 4);
        QByteArray sbytes = fio.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = login.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = persontask.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = report.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);
    }
    UserInformation(QByteArray &ba)
    {
        operation = DBOperation::USER_LINE;
        char *magicHead = getMH();
        quint32 dpos = strlen(magicHead) + 4;
        char *data = &(ba.data())[dpos];
        dpos = 4;
        quint32 op = *(data);
        QByteArray part;
        part.clear();
        part.append(&data[dpos], op);
        fio = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        login = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        persontask = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        report = QString::fromUtf8(part);
        dpos += op;
    }
};
//********************************************************************************
struct TaskUserInformation {
    DBOperation operation;
    QString fio;
    QString login;
    quint8 isActive;
    QString usertask;
    QString report;
    TaskUserInformation()
    {
        operation = DBOperation::TASK_USER_LINE;
    }
    void toBytes(QByteArray &bArray)
    {
        bArray.clear();
        char *magicHead = getMH();
        bArray.append(magicHead, strlen(magicHead));
        unsigned int op = operation;
        bArray.append((char*)&op, 4);
        QByteArray sbytes = fio.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = login.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        bArray.append((isActive) ? 1 : 0);

        sbytes = usertask.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = report.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);
    }
    TaskUserInformation(QByteArray &ba)
    {
        operation = DBOperation::TASK_USER_LINE;
        char *magicHead = getMH();
        quint32 dpos = strlen(magicHead) + 4;
        char *data = &(ba.data())[dpos];
        dpos = 4;
        quint32 op = *(data);
        QByteArray part;
        part.clear();
        part.append(&data[dpos], op);
        fio = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        login = QString::fromUtf8(part);
        dpos += op;
        //-------------
        isActive = *((quint8*)&data[dpos]);
        dpos++;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        usertask = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        report = QString::fromUtf8(part);
        dpos += op;
    }
};
//********************************************************************************
struct AddTaskInf
{
    DBOperation operation;
    QString task, describe;
    QString begDate, endDate;
    QString adminpasswrd;
    AddTaskInf()
    {
        operation = DBOperation::ADD_TASK;
    }
    void toBytes(QByteArray &bArray)
    {
        bArray.clear();
        char *magicHead = getMH();
        bArray.append(magicHead, strlen(magicHead));
        unsigned int op = operation;
        bArray.append((char*)&op, 4);
        QByteArray sbytes = task.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = describe.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = begDate.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = endDate.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = adminpasswrd.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);
    }
    AddTaskInf(QByteArray &ba)
    {
        operation = DBOperation::ADD_TASK;
        char *magicHead = getMH();
        quint32 dpos = strlen(magicHead) + 4;
        char *data = &(ba.data())[dpos];
        dpos = 4;
        quint32 op = *(data);
        QByteArray part;
        part.clear();
        part.append(&data[dpos], op);
        task = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        describe = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        begDate = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        endDate = QString::fromUtf8(part);
        dpos += op;
    }
};
//********************************************************************************
struct AddUserInf
{
    DBOperation operation;
    QString adminpass;
    QString fio;
    QString login;
    QString pass;
    AddUserInf()
    {
        operation = DBOperation::ADD_USER;
    }
    void toBytes(QByteArray &bArray)
    {
        bArray.clear();
        char *magicHead = getMH();
        bArray.append(magicHead, strlen(magicHead));
        unsigned int op = operation;
        bArray.append((char*)&op, 4);
        QByteArray sbytes = adminpass.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = fio.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = login.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = pass.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);
    }
    AddUserInf(QByteArray &ba)
    {
        operation = DBOperation::ADD_USER;
        operation = DBOperation::ADD_TASK;
        char *magicHead = getMH();
        quint32 dpos = strlen(magicHead) + 4;
        char *data = &(ba.data())[dpos];
        dpos = 4;
        quint32 op = *(data);
        QByteArray part;
        part.clear();
        part.append(&data[dpos], op);
        adminpass = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        fio = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        login = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        pass = QString::fromUtf8(part);
        dpos += op;
    }
};
//********************************************************************************
struct UpdateTaskInfo
{
    DBOperation operation;
    QString task;
    QString descibe;
    QString startDate, endDate;
    QString adminpass;
    quint8 progress;
    quint32 idtask;
    UpdateTaskInfo()
    {
        operation = DBOperation::UPDATE_TASK;
    }

    void toBytes(QByteArray &bArray)
    {
        bArray.clear();
        char *magicHead = getMH();
        bArray.append(magicHead, strlen(magicHead));
        unsigned int op = operation;
        bArray.append((char*)&op, 4);

        QByteArray sbytes = task.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = descibe.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = startDate.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = endDate.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = adminpass.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        bArray.append((char)progress);


        bArray.append((char*)&idtask, sizeof idtask);
    }

    UpdateTaskInfo(QByteArray &ba)
    {
        operation = DBOperation::TASK_LINE;
        char *magicHead = getMH();
        quint32 dpos = strlen(magicHead) + 4;
        char *data = &(ba.data())[dpos];
        dpos = 4;
        quint32 op = *(data);
        QByteArray part;
        part.clear();
        part.append(&data[dpos], op);
        task = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        descibe = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        startDate = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        endDate = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        adminpass = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        endDate = QString::fromUtf8(part);
        dpos += op;
        progress = *((quint8*)&data[dpos++]);
        idtask = *((quint32*)&data[dpos]);
    }
};
//********************************************************************************
struct UpdateUserTaskInfo
{
    DBOperation operation;
    QString adminpass;
    QString usertsk;
    QString login;
    quint32 idtask;
    UpdateUserTaskInfo()
    {
        operation = DBOperation::UPDATE_USER_TASK;
    }
    void toBytes(QByteArray &bArray)
    {
        bArray.clear();
        char *magicHead = getMH();
        bArray.append(magicHead, strlen(magicHead));
        unsigned int op = operation;
        bArray.append((char*)&op, 4);

        QByteArray sbytes = adminpass.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = usertsk.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = login.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        bArray.append((char*)&idtask, sizeof idtask);
    }
    UpdateUserTaskInfo(QByteArray &ba)
    {
        operation = DBOperation::UPDATE_USER_TASK;
        char *magicHead = getMH();
        quint32 dpos = strlen(magicHead) + 4;
        char *data = &(ba.data())[dpos];
        dpos = 4;
        quint32 op = *(data);
        QByteArray part;
        part.clear();
        part.append(&data[dpos], op);
        adminpass = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        usertsk = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        login = QString::fromUtf8(part);
        dpos += op;
        //--------------
        idtask = *((quint32*)&data[dpos]);
    }
};
//********************************************************************************
struct UpdateReportInfo
{
    DBOperation operation;
    QString passwrd;
    QString report;
    QString login;
    quint32 idtask;
    UpdateReportInfo()
    {
        operation = DBOperation::UPDATE_REPORT;
    }

    void toBytes(QByteArray &bArray)
    {
        bArray.clear();
        char *magicHead = getMH();
        bArray.append(magicHead, strlen(magicHead));
        unsigned int op = operation;
        bArray.append((char*)&op, 4);

        QByteArray sbytes = passwrd.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = report.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        sbytes = login.toUtf8();
        op = sbytes.size();
        bArray.append((char*)&op, 4);
        bArray.append(sbytes);

        bArray.append((char*)&idtask, sizeof idtask);
    }
    UpdateReportInfo(QByteArray &ba)
    {
        operation = DBOperation::UPDATE_REPORT;
        char *magicHead = getMH();
        quint32 dpos = strlen(magicHead) + 4;
        char *data = &(ba.data())[dpos];
        dpos = 4;
        quint32 op = *(data);

        QByteArray part;
        part.clear();
        part.append(&data[dpos], op);
        passwrd = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        report = QString::fromUtf8(part);
        dpos += op;
        //--------------
        op = *(&data[dpos]);
        dpos += 4;
        part.clear();
        part.append(&data[dpos], op);
        login = QString::fromUtf8(part);
        dpos += op;
        //--------------
        idtask = *((quint32*)&data[dpos]);
    }
};
//********************************************************************************
inline DBOperation testPackege(QByteArray &ba)
{
    char *magicHead = getMH();
    DBOperation operation = DBOperation::NORE;
    quint32 dpos = strlen(magicHead);
    char *data = ba.data();
    if (memcmp(data, magicHead, dpos) != 0) return operation;
    operation = (DBOperation)((unsigned int*)&data[dpos])[0];
    return operation;
}
#endif // HEADER_H
