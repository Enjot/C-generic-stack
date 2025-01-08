#pragma once

#include "handler.h"


void message_error(
    ERROR_TYPE error_type,
    const char *message,
    const char *source
);

void message_debug(const char* message, const char* source);

void message_info(const char *message);
