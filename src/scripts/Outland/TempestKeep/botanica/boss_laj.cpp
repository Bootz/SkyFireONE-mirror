/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: Boss_Laj
SD%Complete: 90
SDComment: Immunities are wrong, must be adjusted to use resistance from creature_templates. Most spells require database support.
SDCategory: Tempest Keep, The Botanica
EndScriptData */

#include "ScriptPCH.h"

#define EMOTE_SUMMON                -1553006

#define SPELL_ALLERGIC_REACTION     34697
#define SPELL_TELEPORT_SELF         34673

#define SPELL_SUMMON_LASHER_1       34681
#define SPELL_SUMMON_FLAYER_1       34682
#define SPELL_SUMMON_LASHER_2       34684
#define SPELL_SUMMON_FLAYER_2       34685
#define SPELL_SUMMON_LASHER_3       34686
#define SPELL_SUMMON_FLAYER_4       34687
#define SPELL_SUMMON_LASHER_4       34688
#define SPELL_SUMMON_FLAYER_3       34690

#define MODEL_DEFAULT               13109
#define MODEL_ARCANE                14213
#define MODEL_FIRE                  13110
#define MODEL_FROST                 14112
#define MODEL_NATURE                14214

struct boss_lajAI : public ScriptedAI
{
    boss_lajAI(Creature *c) : ScriptedAI(c) {}

    bool CanSummon;
    uint32 Teleport_Timer;
    uint32 Summon_Timer;
    uint32 Transform_Timer;
    uint32 Allergic_Timer;

    void Reset()
    {
        me->SetUInt32Value(UNIT_FIELD_DISPLAYID,MODEL_DEFAULT);
        me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_SHADOW, true);
        me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_ARCANE, false);
        me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FIRE, false);
        me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FROST, false);
        me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_NATURE, false);

        CanSummon = false;
        Teleport_Timer = 20000;
        Summon_Timer = 2500;
        Transform_Timer = 30000;
        Allergic_Timer = 5000;
    }

    void DoTransform()
    {
        switch(rand()%5)
        {
            case 0:
                me->SetUInt32Value(UNIT_FIELD_DISPLAYID,MODEL_DEFAULT);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_SHADOW, true);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_ARCANE, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FIRE, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FROST, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_NATURE, false);
                break;
            case 1:
                me->SetUInt32Value(UNIT_FIELD_DISPLAYID,MODEL_ARCANE);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_SHADOW, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_ARCANE, true);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FIRE, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FROST, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_NATURE, false);
                break;
            case 2:
                me->SetUInt32Value(UNIT_FIELD_DISPLAYID,MODEL_FIRE);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_SHADOW, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_ARCANE, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FIRE, true);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FROST, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_NATURE, false);
                break;
            case 3:
                me->SetUInt32Value(UNIT_FIELD_DISPLAYID,MODEL_FROST);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_SHADOW, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_ARCANE, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FIRE, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FROST, true);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_NATURE, false);
                break;
            case 4:
                me->SetUInt32Value(UNIT_FIELD_DISPLAYID,MODEL_NATURE);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_SHADOW, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_ARCANE, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FIRE, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FROST, false);
                me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_NATURE, true);
                break;
        }
    }

    void DoSummons()
    {
        switch(rand()%4)
        {
            case 0:
                DoCast(me,SPELL_SUMMON_LASHER_1,true);
                DoCast(me,SPELL_SUMMON_FLAYER_1,true);
                break;
            case 1:
                DoCast(me,SPELL_SUMMON_LASHER_2,true);
                DoCast(me,SPELL_SUMMON_FLAYER_2,true);
                break;
            case 2:
                DoCast(me,SPELL_SUMMON_LASHER_3,true);
                DoCast(me,SPELL_SUMMON_FLAYER_3,true);
                break;
            case 3:
                DoCast(me,SPELL_SUMMON_LASHER_4,true);
                DoCast(me,SPELL_SUMMON_FLAYER_4,true);
                break;
        }
        CanSummon = false;
    }

    void EnterCombat(Unit *who)
    {
    }

    void JustSummoned(Creature *summon)
    {
        if (summon && me->getVictim())
            summon->AI()->AttackStart(SelectUnit(SELECT_TARGET_RANDOM, 0));
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (CanSummon)
        {
            if (Summon_Timer <= diff)
            {
                DoScriptText(EMOTE_SUMMON, me);
                DoSummons();
                Summon_Timer = 2500;
            } else Summon_Timer -= diff;
        }

        if (Allergic_Timer <= diff)
        {
            DoCast(me->getVictim(),SPELL_ALLERGIC_REACTION);
            Allergic_Timer = 25000+rand()%15000;
        } else Allergic_Timer -= diff;

        if (Teleport_Timer <= diff)
        {
            DoCast(me,SPELL_TELEPORT_SELF);
            Teleport_Timer = 30000+rand()%10000;
            CanSummon = true;
        } else Teleport_Timer -= diff;

        if (Transform_Timer <= diff)
        {
            DoTransform();
            Transform_Timer = 25000+rand()%15000;
        } else Transform_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_laj(Creature* pCreature)
{
    return new boss_lajAI (pCreature);
}

void AddSC_boss_laj()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_laj";
    newscript->GetAI = &GetAI_boss_laj;
    newscript->RegisterSelf();
}
