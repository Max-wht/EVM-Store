//SPDX-License-Identifier: GPL-3.0-only
pragma solidity 0.8.30;

import {BaseTestV1} from "./BaseTestV1.t.sol";
import {HuffDeployer} from "foundry-huff/HuffDeployer.sol";
import {HorseStore} from "../../src/horseStoreV1/HorseStore.sol";

contract HorseStoreHuff is BaseTestV1 {
    string public constant HORSE_STORE_LOCATION = "horseStoreV1/HorseStore";

    function setUp() public override {
        horseStore = HorseStore(
            HuffDeployer.config().deploy(HORSE_STORE_LOCATION)
        );
    }
}
