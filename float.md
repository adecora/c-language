# Float numbers

$
<------------ 32 bit ------------->
   sign     exponent    mantisa
<- 1 bit-> <- 8 bit -> <- 23 bit ->

`(-1)^s * 1 * mantisa * 2^(exponet - 127)`
$

La mantisa empezando por la iznquiersda representa: 2⁻¹, 2⁻²... 2⁻²³.


### Ejemplos:

**float _some_random_value = 0.3;**

1050253722 = 0 01111101 00110011001100110011010

sign = 0
exp = 125
mantisa = 0.20000004768371582

-(1)⁰ * (1 + 0.20000004768371582) * 2 ^ (125 - 127) = 0.30000001192092896


**float _some_random_value = 5.0;**

> Sería algo como: `1.25 * 2²`.

1084227584 = 0 10000001 01000000000000000000000

sign = 0
exp = 129
mantisa = 0.25

-(1)⁰ * (1 + 0.25) * 2 ^ (129 - 127) = 5.0


# Double representation

$
<------------ 64 bit -------------->
   sign     exponent    mantisa
<- 1 bit-> <- 11 bit -> <- 52 bit ->

`(-1)^s * 1 * mantisa * 2^(exponent - 1023)`
$



**float _some_random_value = 5.0;**

.word	0           = lower  4 bytes
.word	1075052544  = higher 4 bytes

0 10000000001 0100000000000000000000000000000000000000000000000000

sign = 0
exp = 1025
mantisa = 0.25

-(1)⁰ * (1 + 0.25) * 2 ^ (1025 - 1023) = 5.0