// SPDX-License-Identifier: GPL-3.0-only
pragma solidity 0.8.30;

import {Test, console2} from "forge-std/Test.sol";
import {HorseStore} from "../../src/horseStoreV1/HorseStore.sol";

abstract contract BaseTestV1 is Test {
    HorseStore public horseStore;

    function setUp() public virtual {
        horseStore = new HorseStore();
    }

    function testReadValue() public {
        uint256 initialValue = horseStore.readNumberOfHorses();
        assertEq(initialValue, 0);
    }

    function testUpdateValue() public {
        horseStore.updateHorseNumber(1);
        uint256 updatedValue = horseStore.readNumberOfHorses();
        assertEq(updatedValue, 1);
    }
}
