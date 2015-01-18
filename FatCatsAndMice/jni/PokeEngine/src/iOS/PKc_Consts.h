#ifndef _PKc_CONSTS_H_
#define _PKc_CONSTS_H_

#define PKc_IOS_VERSION_6_0 @"6.0"

// Verifica a versao do SO
#define SYSTEM_VERSION_LESS_THAN(v) ([[[UIDevice currentDevice] systemVersion] \
compare:v options:NSNumericSearch] == NSOrderedAscending)


#endif