#!/bin/sh

rm -rf ./results/
mkdir results
../../build/BattleEngine < test_fireball.json |python -m json.tool > results/FireballResults.txt
../../build/BattleEngine < test_snipe.json |python -m json.tool > results/SnipeResults.txt
../../build/BattleEngine < test_smash.json |python -m json.tool > results/SmashResults.txt
../../build/BattleEngine < test_ghostarrow.json |python -m json.tool > results/GhostarrowResults.txt
../../build/BattleEngine < test_meteor.json |python -m json.tool > results/MeteorResults.txt
../../build/BattleEngine < test_meteor_onself.json |python -m json.tool > results/MeteorOnselfResults.txt
../../build/BattleEngine < test_bladestorm.json |python -m json.tool> results/BladestormResults.txt
../../build/BattleEngine < test_shieldbreak.json |python -m json.tool > results/MeteorResults.txt
../../build/BattleEngine < test_shadowstep.json |python -m json.tool > results/ShadowstepResults.txt
../../build/BattleEngine < test_foresight.json |python -m json.tool > results/foresightResults.txt
../../build/BattleEngine < test_holyhand.json |python -m json.tool > results/HolyhandResults.txt
../../build/BattleEngine < test_holywell.json |python -m json.tool > results/HolywellResults.txt
../../build/BattleEngine < test_coldfeet.json |python -m json.tool > results/ColdfeetResults.txt
../../build/BattleEngine < test_heavypoison.json |python -m json.tool > results/HeavypoisonResults.txt
