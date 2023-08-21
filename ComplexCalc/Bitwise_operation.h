#ifndef Bitwise_operation_H
#define Bitwise_operation_H

# define Set_Bit(var,bitno) (var)|=(1<<(bitno))

# define Clear_Bit(var,bitno) (var)&=(~(1<<(bitno)))

# define Togle_Bit(var,bitno) (var)^=(1<<(bitno))

# define get_bit(var,bitno) (((var)>>(bitno))&(1))

#endif
