#ifndef SCRIPTGLOBAL_H_INCLUDED
#define SCRIPTGLOBAL_H_INCLUDED
#include <angelscript.h>


namespace Scripting{
    void print(std::string &msg)
    {
        printf("%s", msg.c_str());
    }

    void MessageCallback(const asSMessageInfo*msg, void * param)
    {
        const char *type = "ERR ";
        if(msg->type == asMSGTYPE_WARNING)
            type = "WARN";
        else if(msg->type == asMSGTYPE_INFORMATION)
            type = "INFO";

        printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
    }

}

#endif // SCRIPTGLOBAL_H_INCLUDED
