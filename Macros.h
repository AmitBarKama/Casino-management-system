#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define UNDER_21(num) ((num) < 21)
#define DEALER_HIT(num) ((num) < 17 && UNDER_21(num))
#define IS_BIGGER(x, y)	(x) > (y) ? 1 : 0
#define IS_ZERO(num) ((num) == 0)
#define IS_BETWEEN(num, a, b) ((num) >= (a) && (num) <= (b))
#define IS_EVEN(num) ((num) % 2 == 0)