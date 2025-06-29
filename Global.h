#pragma once
#include "clsAdmin.h"
#include "clsMember.h"

// Declare the global logged-in admin
extern clsAdmin CurrentAdmin = clsAdmin::Find("","");
extern clsMember CurrentMember = clsMember::Find("", "");

