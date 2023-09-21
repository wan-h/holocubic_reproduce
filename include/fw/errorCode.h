#ifndef _ERROR_CODE_H_
#define _ERROR_CODE_H_

typedef enum ErrorCode {
    // OK
    CODE_OK = 0,
    // WARN
    CODE_WARN = 10,
    // ERROR
    CODE_ERROR = 100,
    CODE_ERROR_INIT_CHECK = 101,
};

#endif // !_ERROR_CODE_H_