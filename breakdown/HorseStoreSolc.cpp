//.CPP just for the text highlight

//@note: 0x6080604052348015600e575f5ffd5b506101298061001c5f395ff3fe6080604052348015600e575f5ffd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c01714604c575b5f5ffd5b604a60048036038101906046919060a9565b6066565b005b6052606f565b604051605d919060dc565b60405180910390f35b805f8190555050565b5f5f54905090565b5f5ffd5b5f819050919050565b608b81607b565b81146094575f5ffd5b50565b5f8135905060a3816084565b92915050565b5f6020828403121560bb5760ba6077565b5b5f60c6848285016097565b91505092915050565b60d681607b565b82525050565b5f60208201905060ed5f83018460cf565b9291505056fea2646970667358221220c16bd1787a194f0fde7d9b06c18f6d959dd7f81be6f794ed364664267855e20964736f6c634300081e0033

//@note 1.Contract Create Bytecode 2.runtime bytecode 3.metadata

//@follow contract create bytecode
//Free memory pointer
PUSH1 0x80 // top [0x80] bottom
PUSH1 0x40 // top [0x40 0x80] bottom 
MSTORE // top [offset value] bottom
// put 0x80 in the index of 0x40 in memory
//@note:offset    [0x00] [0x20] [0x40] ... [0x80]
//                               0x80
//@note:slot        0      1      2
                  hash    hash   freepointer

//@note jump (in case of nonpayable constructor)
CALLVALUE // top [msg.value] bottom
DUP1 
ISZERO // top [msg.value==0 msg.value] bottom
PUSH1 0x0e
JUMPI // top [msg.value] bottom
PUSH0
PUSH0
REVERT

//@note store runtime bytecode to memory
JUMPDEST //0x0e
POP // []
PUSH2 0x0129 // top [0x0129] bottom
DUP1 // top [0x0129 0x0129] bottom
PUSH2 0x001c // top [0x001c 0x0129 0x0129] bottom
PUSH0 // top [0x00 0x001c 0x0129 0x0129] bottom
CODECOPY // top [0x0129] bottom  memory [runtime bytecode]
PUSH0 // top [0x00 0x0129] bottom
//[offset in memory, length in memory]
RETURN // []
INVALID

//@follow runtime bytecode
//@note entry point of all call
//free memory pointer setup
PUSH1 0x80 // 0x001c
PUSH1 0x40
MSTORE
//nonpayable
CALLVALUE
DUP1
ISZERO
PUSH1 0x0e
JUMPI
PUSH0
PUSH0
REVERT

//@note check if calldata size is less than 0x04
JUMPDEST
POP
PUSH1 0x04 // top [0x04] bottom
CALLDATASIZE // top [cds 0x04] bottom
LT // top [cds < 0x04] bottom
PUSH1 0x30 // top [0x30 cds < 0x04] bottom
JUMPI

//@note functions dispatcher
PUSH0 // top [0x00] bottom
CALLDATALOAD // top [32_bytes_of_calldata] bottom
PUSH1 0xe0
SHR
DUP1 // top [selector selector] bottom
//@note case1 updateHorseNumber selector
PUSH4 0xcdfead2e
EQ
PUSH1 0x34
JUMPI
//@note case2 readNumberOfHorses selector
DUP1
PUSH4 0xe026c017
EQ
PUSH1 0x4c
JUMPI

//@note:calldata<0x04 jumpdest
JUMPDEST
PUSH0
PUSH0
REVERT

//@note: function updateHorseNumber(uint256) router
JUMPDEST
PUSH1 0x4a 
PUSH1 0x04
DUP1          // top [0x04 0x04 0x4a selector] bottom
CALLDATASIZE  // top [cds 0x04 0x04 0x4a selector] bottom
SUB           // top [cds-4 0x04 0x4a selector] bottom
DUP2          // top [0x04 cds-0x04 0x04 0x4a selector] bottom
ADD           // top [cds 0x04 0x4a selector] bottom
SWAP1         // top [0x04 cds 0x4a selector] bottom
PUSH1 0x46    // top [0x46 0x04 cds 0x4a selector] bottom
SWAP2         // top [cds 0x04 0x46 0x4a selector] bottom
SWAP1         // top [0x04 cds 0x46 0x4a selector] bottom
PUSH1 0xa9    // top [0xa9 0x04 cds 0x46 0x4a selector] bottom
JUMP          //@note jump[updateHorseNumber_index_1]

JUMPDEST
PUSH1 0x66
JUMP
JUMPDEST
STOP

//@note: function readNumberOfHorses() 0x4c
JUMPDEST
PUSH1 0x52     // top [0x52 selector] bottom
PUSH1 0x6f     // top [0x6f 0x52 selector] bottom
JUMP           //@note jump[readNumberOfHorses_index_1]

JUMPDEST
PUSH1 0x40
MLOAD
PUSH1 0x5d
SWAP2
SWAP1
PUSH1 0xdc
JUMP
JUMPDEST
PUSH1 0x40
MLOAD
DUP1
SWAP2
SUB
SWAP1
RETURN
JUMPDEST
DUP1
PUSH0
DUP2
SWAP1
SSTORE
POP
POP
JUMP

//@note: function [readNumberOfHorses_index_1]
JUMPDEST
PUSH0
PUSH0
SLOAD
SWAP1
POP
SWAP1
JUMP

//@note: revert() 0x77
JUMPDEST
PUSH0
PUSH0
REVERT

//@note: 0x7b
JUMPDEST
PUSH0
DUP2
SWAP1
POP
SWAP2
SWAP1
POP
JUMP
JUMPDEST
PUSH1 0x8b
DUP2
PUSH1 0x7b
JUMP
JUMPDEST
DUP2
EQ
PUSH1 0x94
JUMPI
PUSH0
PUSH0
REVERT
JUMPDEST
POP
JUMP
JUMPDEST
PUSH0
DUP2
CALLDATALOAD
SWAP1
POP
PUSH1 0xa3
DUP2
PUSH1 0x84
JUMP
JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP

//@note jump[updateHorseNumber_index_1] :whether the function call has params
JUMPDEST     // top [0x04 cds 0x46 0x4a selector] bottom
PUSH0        // top [0x00 0x04 cds 0x46 0x4a selector] bottom
PUSH1 0x20   // top [0x20 0x00 0x04 cds 0x46 0x4a selector] bottom
DUP3         // top [0x04 0x20 0x00 0x04 cds 0x46 0x4a selector] bottom
DUP5         // top [cds 0x04 0x20 0x00 0x04 cds 0x46 0x4a selector] bottom
SUB          // top [cds-0x04 0x20 0x00 0x04 cds 0x46 0x4a selector] bottom
SLT          // top [cds-0x04<0x20 0x00 0x04 cds 0x46 0x4a selector] bottom
//it means the function call has params
/*
if(cds-4<32){
    cds-4<32==false = false
}else{
    cds-4<32==false = true
}
output^-1 = input
*/
ISZERO       // top [mcda? 0x00 0x04 cds 0x46 0x4a selector] bottom
PUSH1 0xbb
JUMPI //@note jump[updateHorseNumber_index_1_1]

//revert
PUSH1 0xba   // top [0xba 0x00 0x04 cds 0x46 0x4a selector] bottom
PUSH1 0x77   // top [0x77 0xba 0x00 0x04 cds 0x46 0x4a selector] bottom
JUMP

//@note: 0xba
JUMPDEST

//@note: 0xbb
JUMPDEST //@note jump[updateHorseNumber_index_1_1]
PUSH0         // top [0x00 0x00 0x04 cds 0x46 0x4a selector] bottom
PUSH1 0xc6    //
DUP5
DUP3
DUP6
ADD
PUSH1 0x97
JUMP
JUMPDEST
SWAP2
POP
POP
SWAP3
SWAP2
POP
POP
JUMP
JUMPDEST
PUSH1 0xd6
DUP2
PUSH1 0x7b
JUMP
JUMPDEST
DUP3
MSTORE
POP
POP
JUMP
JUMPDEST
PUSH0
PUSH1 0x20
DUP3
ADD
SWAP1
POP
PUSH1 0xed
PUSH0
DUP4
ADD
DUP5
PUSH1 0xcf
JUMP
JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP

//@note 
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
INVALID
PUSH12 0xd1787a194f0fde7d9b06c18f
PUSH14 0x959dd7f81be6f794ed3646642678
SSTORE
INVALID
MULMOD
PUSH5 0x736f6c6343
STOP
ADDMOD
CLZ
STOP
CALLER