// SPDX-License-Identifier: GPL-3.0-only
pragma solidity 0.8.30;

import {Test, console2} from "forge-std/Test.sol";
import {HorseStoreYul} from "../../src/horseStoreV1/HorseStoreYul.sol";
import {HorseStore} from "../../src/horseStoreV1/HorseStore.sol";
import {BaseTestV1} from "./BaseTestV1.t.sol";

contract HorseStoreYulTest is BaseTestV1 {
    function setUp() public override {
        horseStore = HorseStore(address(new HorseStoreYul()));
    }
}
