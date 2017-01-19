#include <iostream>
#include "SpellFactory.hpp"
#include "DamageEffect.hpp"
#include "HealEffect.hpp"
#include "TrapEffect.hpp"
#include "LineAoeEffect.hpp"
#include "CrossAoeEffect.hpp"
#include "TrapSpell.hpp"
#include "BumpEffect.hpp"
#include "BuffEffect.hpp"
#include "InvisibleEffect.hpp"
#include "VisibleEffect.hpp"
#include "RemoveSpeedEffect.hpp"
#include "SilenceEffect.hpp"
#include "StunEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		void SpellFactory::init() {
			//spell registration : name, power, minrange, range, cooldown, active, aoe, los
			std::shared_ptr<IEffect> m_fireball[] = {std::make_shared<DamageEffect>()};
			std::list<std::shared_ptr<IEffect> > fireball(m_fireball, m_fireball + sizeof(m_fireball) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("FIREBALL", std::make_shared<Spell>(fireball,
					"FIREBALL",1,5,1,1,1,3,1));


			std::shared_ptr<IEffect> m_holyhand[] = {std::make_shared<HealEffect>()};
			std::list<std::shared_ptr<IEffect> > holyhand(m_holyhand, m_holyhand + sizeof(m_holyhand) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("HOLY_HAND", std::make_shared<Spell>(holyhand,
					"HOLY_HAND",0.7,3,1,1,1,0,1));


			std::shared_ptr<IEffect> m_snipe[] = {std::make_shared<DamageEffect>()};
			std::list<std::shared_ptr<IEffect> > snipe(m_snipe, m_snipe + sizeof(m_snipe) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("SNIPE", std::make_shared<Spell>(snipe,
					"SNIPE",1,7,1,1,1,0,1));

			std::shared_ptr<IEffect> m_firetrap[] = {std::make_shared<TrapEffect>(std::make_shared<DamageEffect>())};
			std::list<std::shared_ptr<IEffect> > firetrap(m_firetrap, m_firetrap + sizeof(m_firetrap) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("FIRE_TRAP", std::make_shared<Spell>(firetrap,
					"FIRE_TRAP",0.8,5,3,1,1,0,1));


			std::shared_ptr<IEffect> m_ghostarrow[] = {std::make_shared<LineAoeEffect>(5, std::make_shared<DamageEffect>())};
			std::list<std::shared_ptr<IEffect> > ghostarrow(m_ghostarrow, m_ghostarrow + sizeof(m_ghostarrow) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("GHOST_ARROW", std::make_shared<Spell>(ghostarrow,
					"GHOST_ARROW",0.8,3,5,1,1,0,1));


			std::shared_ptr<IEffect> m_smash[] = {std::make_shared<LineAoeEffect>(2, std::make_shared<DamageEffect>())};
			std::list<std::shared_ptr<IEffect> > smash(m_smash, m_smash + sizeof(m_smash) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("SMASH", std::make_shared<Spell>(smash,
					"SMASH",2,1,2,1,2,0,1));


			std::shared_ptr<IEffect> m_bladestorm[] = {std::make_shared<CrossAoeEffect>(2, std::make_shared<DamageEffect>())};
			std::list<std::shared_ptr<IEffect> > bladestorm(m_bladestorm, m_bladestorm + sizeof(m_bladestorm) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("BLADESTORM", std::make_shared<Spell>(bladestorm,
					"BLADESTORM",1,1,1,1,2,0,1));


			std::shared_ptr<IEffect> m_meteor[] = {std::make_shared<CrossAoeEffect>(3, std::make_shared<DamageEffect>()) };
			std::list<std::shared_ptr<IEffect> > meteor(m_meteor, m_meteor + sizeof(m_meteor) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("METEOR", std::make_shared<Spell>(meteor,
					"METEOR",1.5,5,3,1,3,3,1));

			registerSpell("TRAP", std::make_shared<TrapSpell>());


			std::shared_ptr<IEffect> m_shieldbump[] = {std::make_shared<DamageEffect>(), std::make_shared<BumpEffect>(nullptr)};
			std::list<std::shared_ptr<IEffect> > shieldbump(m_shieldbump, m_shieldbump + sizeof(m_shieldbump) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("SHIELD_BUMP", std::make_shared<Spell>(shieldbump,
					"SHIELD_BUMP",1,1,3,1,1,0,1));



			std::shared_ptr<IEffect> m_shieldbreak[] = {std::make_shared<CrossAoeEffect>(1, std::make_shared<BumpEffect>(nullptr))};
			std::list<std::shared_ptr<IEffect> > shieldbreak(m_shieldbreak, m_shieldbreak + sizeof(m_shieldbreak) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("SHIELD_BREAK", std::make_shared<Spell>(shieldbreak,
					"SHIELD_BREAK",1.5,5,3,1,3,0,1));


			std::shared_ptr<IEffect> m_curse[] = {std::make_shared<BuffEffect>(3, std::make_shared<DamageEffect>())};
			std::list<std::shared_ptr<IEffect> > curse(m_curse, m_curse + sizeof(m_curse) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("CURSE", std::make_shared<Spell>(curse,
					"CURSE",1.5,5,3,1,3,1,0,3));


		std::shared_ptr<IEffect> m_shadowstep[] = {std::make_shared<InvisibleEffect>()};
			std::list<std::shared_ptr<IEffect> > shadowstep(m_shadowstep, m_shadowstep + sizeof(m_shadowstep) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("SHADOW_STEP", std::make_shared<Spell>(shadowstep,
					"SHADOW_STEP",0,0,0,2,0,0,0,0));

			std::shared_ptr<IEffect> m_foresight[] = {std::make_shared<CrossAoeEffect>(5, std::make_shared<VisibleEffect>()) };
			std::list<std::shared_ptr<IEffect> > foresight(m_foresight, m_foresight + sizeof(m_foresight) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("FORESIGHT", std::make_shared<Spell>(foresight,
					"FORESIGHT",1.5,5,3,1,3,3,1));

			std::shared_ptr<IEffect> m_holywell[] = {std::make_shared<BuffEffect>(3, std::make_shared<CrossAoeEffect>(3, std::make_shared<HealEffect>()))};
			std::list<std::shared_ptr<IEffect> > holywell(m_holywell, m_holywell + sizeof(m_holywell) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("HOLY_WELL", std::make_shared<Spell>(holywell,
					"HOLY_WELL",1.5,5,3,1,3,1,0,3));

			std::shared_ptr<IEffect> m_coldfeet[] = {std::make_shared<BuffEffect>(1, std::make_shared<RemoveSpeedEffect>(0)), std::make_shared<DamageEffect>()};
			std::list<std::shared_ptr<IEffect> > coldfeet(m_coldfeet, m_coldfeet + sizeof(m_coldfeet) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("COLDFEET", std::make_shared<Spell>(coldfeet,
					"COLDFEET",0.3,5,3,1,3,1,0,3));

			std::shared_ptr<IEffect> m_heavypoison[] = {std::make_shared<BuffEffect>(2, std::make_shared<RemoveSpeedEffect>(3)), std::make_shared<DamageEffect>()};
			std::list<std::shared_ptr<IEffect> > heavypoison(m_heavypoison, m_heavypoison + sizeof(m_heavypoison) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("HEAVY_POISON", std::make_shared<Spell>(heavypoison,
					"HEAVY_POISON",0.5,5,3,1,3,1,0,3));

			std::shared_ptr<IEffect> m_dazzle[] = {std::make_shared<StunEffect>(),std::make_shared<DamageEffect>()};
			std::list<std::shared_ptr<IEffect> > dazzle(m_dazzle, m_dazzle+ sizeof(m_dazzle) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("DAZZLE", std::make_shared<Spell>(dazzle,
					"DAZZLE",0.8,5,3,1,3,1,0,3));

			std::shared_ptr<IEffect> m_dazzlingpoisong[] = {std::make_shared<SilenceEffect>(),std::make_shared<DamageEffect>()};
			std::list<std::shared_ptr<IEffect> > dazzlingpoisong(m_dazzlingpoisong, m_dazzlingpoisong+ sizeof(m_dazzlingpoisong) / sizeof(std::shared_ptr<IEffect>));
			registerSpell("DAZZLING_POISON", std::make_shared<Spell>(dazzlingpoisong,
					"DAZZLING_POISON",1,5,3,1,3,1,0,3));

			registerSpell("TRAP", std::make_shared<TrapSpell>());

			std::cerr << "spell factory initialised" << std::endl;
		}

		void SpellFactory::registerSpell(
			std::string const& n,
			std::shared_ptr<ISpell> spell) {
			m_dictionary[n] = spell;
		}

		std::shared_ptr<ISpell> SpellFactory::get(std::string const& n) {
			if (m_dictionary.find(n) != m_dictionary.end())
				return (m_dictionary[n]);
			return nullptr;
		}

		SpellFactory::~SpellFactory() {
		}
	}
}
