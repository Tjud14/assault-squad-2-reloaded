{"tank"
;   {friction 1}
;   {restitution 0.3}
    (include "tank/general_scripts_defines.inc")

;MEGA BUILDING BEGIN
=============================================================================================================================================================================
    (define "damage_process_pierce" ;by Svoyak  ;define's call's see in tank-armoredcar.inc, tank-light.inc, tank-medium.inc & tank-heavy.inc.
;=================================
                {if stuff "%staff"
                    ("gun_hit" rand(%pierce_gun))
                    ("track_hit" max_rand(%pierce_front_back_track) min_rand(%pierce_left_right_track))
                    {if volume "body"
                        {burn fx "smoke_dead_tank3" fake}

                        {if rand %pierce_body__kill_charger {kill_crew "charger"}}
                        {if rand %pierce_body__kill_driver {kill_crew "driver"}}
                        {if rand %pierce_body__kill_gunner {kill_crew "gunner"}}
                        {if rand %pierce_body__kill_commander {kill_crew "commander"}}
                        {if rand %pierce_body__kill_gunner2 {kill_crew "gunner2"}}

                        {if rand %pierce_body__body_brake
                            {if work "body"
                                {components "body" break}
                                {unlink_trailer}
                                {call "stat_body_break"}
                                {damage_report "body" "component/body_break"}
                                {delay 2
                                    {crew_emit}
                                }
                                {delay 4
                                    {crew_emit}
                                }
                                {delay 6
                                    {crew_emit}
                                }
                                {able "select" 0}
								else
									{delay 2
										{crew_emit}
									}
									{delay 4
										{crew_emit}
									}
									{delay 6
										{crew_emit}
									}
                            }
						else rand %pierce_body__body_destroy
							{call "mp_destroy"}
							{if rand 0.35 
								{call "explosive_broken"}
							}
                            {delay 2
								{able "select" 0}
                            }
                        else operatable 
                            {damage_report "body" "component/shock"}
                        else
                            {damage_report "body" "component/body_pierced"}
                        }

                            ;================��������� ��������
                            {if operatable
                                {if work "mover"
                                        {chassis_work 0}
                                        {tags add "stopped"}
                                }
                                {if work "turret"
                                    {ik_enable "turret" 0}
                                    {tags add "turr_jummed"}
                                }
                                {weapon_work "gun" 0}{weapon_work "gun2" 0}{weapon_work "mgun" 0}{weapon_work "mgun1" 0}{weapon_work "mgun2" 0}{weapon_work "mgun3" 0}
								{stunned 1}
                                {delay %crew_shock_time
                                    {if not tagged "gun_brake"
                                        {weapon_work "gun" 1}
                                    }
                                    {weapon_work "gun2" 1}{weapon_work "mgun" 1}{weapon_work "mgun1" 1}{weapon_work "mgun2" 1}{weapon_work "mgun3" 1}
									{stunned 0}
                                    {if tagged "stopped"
                                        {tags remove "stopped"}
                                        {if work "mover"
                                            {if not tagged "engine_brake"
                                                {chassis_work 1}
                                            }
                                        }
                                    }
                                    {if tagged "turr_jummed"
                                        {if tagged "turret_brake"
                                            {tags remove "turr_jummed"}
                                        else tagged "turret_stopped_by_body"
                                            {tags remove "turr_jummed"}
                                        else
                                            {tags remove "turr_jummed"}
                                            {ik_enable "turret" 1}
                                        }
                                    }
                                }

                            }

                    else volume "turret"
                        {burn fx "smoke_dead_tank3" fake}

                        {if rand %pierce_turret__explosive
                            {call "stat_break"}
                            {delay 0.5
                                {call "_explosion"}
                            }
                        }
                        {if hit_side front
                           {if rand %pierce_turret_front__gun_brake
                                {if work "gun"
                                    {components "gun" break}
                                    {damage_report "gun" "component/gun_broken"}
                                }
                            }

                            {if rand %pierce_turret_front__turret_brake
                                {components "turret" break}
                                {ik_enable "turret" 0}
                            }

                        else hit_side back
                            {if rand %pierce_turret_back__gun_brake
                                {if work "gun"
                                    {components "gun" break}
                                    {damage_report "gun" "component/gun_broken"}
                                }
                            }

                            {if rand %pierce_turret_back__turret_brake
                                {components "turret" break}
                                {ik_enable "turret" 0}
                            }

                        else
                            {if rand %pierce_turret_left_right__gun_brake
                                {if work "gun"
                                    {components "gun" break}
                                    {damage_report "gun" "component/gun_broken"}
                                }
                            }
                            {if rand %pierce_turret_left_right__turret_brake
                                {components "turret" break}
                                {ik_enable "turret" 0}
                            }
                        }
                        {if rand %pierce_turret__kill_charger {kill_crew "charger"}}
                        {if rand %pierce_turret__kill_driver {kill_crew "driver"}}
                        {if rand %pierce_turret__kill_gunner {kill_crew "gunner"}}
                        {if rand %pierce_turret__kill_commander {kill_crew "commander"}}
                        {if rand %pierce_turret__kill_gunner2 {kill_crew "gunner2"}}

                        ;==============��������� ��������
                        {if operatable
                                    {ik_enable "turret" 0}
                                    {weapon_work "gun" 0}{weapon_work "gun2" 0}{weapon_work "mgun" 0}{weapon_work "mgun1" 0}{weapon_work "mgun2" 0}{weapon_work "mgun3" 0}
									{stunned 1}
                                    {tags add "turr_jummed"}
                                    {delay %crew_shock_time
                                        {if not tagged "gun_brake"
                                            {weapon_work "gun" 1}
                                        }
                                        {weapon_work "gun2" 1}{weapon_work "mgun" 1}{weapon_work "mgun1" 1}{weapon_work "mgun2" 1}{weapon_work "mgun3" 1}
										{stunned 0}
                                        {if tagged "turr_jummed"
                                                {if tagged "turret_brake"
                                                    {tags remove "turr_jummed"}
                                                else tagged "turret_stopped_by_body"
                                                    {tags remove "turr_jummed"}
                                                else
                                                    {tags remove "turr_jummed"}
                                                    {ik_enable "turret" 1}
                                                }
                                        }
                                    }
                        }

                    else volume "mantlet"
                           {burn fx "smoke_dead_tank3" fake}

                            {if rand (* %pierce_mantlet__gun_brake 0.7)
                                {if work "gun"
                                    {components "gun" break}
                                    {damage_report "gun" "component/gun_broken"}
                                }
                            else
                                {call "turret_break"}
                            }
                            ;{if rand %pierce_turret_front__turret_brake
                            ;   {components "turret" break}
                            ;}

                    else volume "explosive"
                        {if rand (* %pierce_inventory__explosive 0.4)
                            {call "explosion"}
                        }
                    else volume "engine"
                        {if rand %pierce_engine__engine_brake
                            {if work "engine"
                                {components "engine" break}
                            }
                            {if rand %pierce_engine__engine_burn
                                {delay 3 2
                                    {call "_burn"}
                                }
                            }
                        }
                    }
                };stuff
    )
    (define "damage_process_bullet_hit" ;by Svoyak
;====================================
                    {if stuff "%staff"
                    {impulse dir %imp}
                    ;{if hit_angle > %angle_hit
                        {if volume "body"
                                {if rand %hit_body__explosive
                                    {call "explosion"}
                                }
                                {if rand %hit_body__engine_brake
                                    {if work "engine"
                                        {components "engine" break}
                                    }
                                }
                                {if rand %hit_body__body_destroy
                                    {call "mp_destroy"}
                                else rand %hit_body__body_brake
                                    {components "body" break}
                                    {damage_report "body" "component/body_break"}
                                }
                            
                        else volume "engine"
                                {if rand %hit_body__explosive
                                    {call "explosion"}
                                }
                                {if rand %hit_engine__engine_brake
                                    {if work "engine"
                                        {components "engine" break}
                                    }
                                }
                                {if rand %hit_body__body_brake
                                    {components "body" break}
                                    {damage_report "body" "component/body_break"}
                                }
                        else volume "turret"
                                {if rand %hit_turret__explosive
                                    {call "explosion"}
                                }
                                {if hit_side front
                                    {if rand %hit_turret_front__gun_brake
                                        {if work "gun"
                                            {components "gun" break}
                                            {damage_report "gun" "component/gun_broken"}
                                        }
                                    }
                                }
                                {if rand %hit_turret__turret_destroy
                                    {components "turret" destroy}
                                else rand %hit_turret__turret_brake
                                    {components "turret" break}
                                }
                        else volume "mantlet"
                                {if rand %hit_turret__explosive
                                    {call "explosion"}
                                }
                                {if rand %hit_turret_front__gun_brake
                                    {if work "gun"
                                        {components "gun" break}
                                        {damage_report "gun" "component/gun_broken"}
                                    }
                                }
                                {if rand %hit_turret__turret_destroy
                                    {components "turret" destroy}
                                else rand %hit_turret__turret_brake
                                    {components "turret" break}
                                }
                        }
                    ;};if hit_angle end
                    }; stuff
;=====================================
    )

    (define "blast_damage_contusion" ;by Svoyak
        {if volume "trackleft"
            ;do nothing
        else volume "trackright"
            ;do nothing
        else volume "roller"
            ;do nothing
        else volume "wheel_work"
            ;do nothing
        else volume "wheel"
            ;do nothing
        else
            {if operatable
                {if not "already_blasted"
            
                    {if min_energy %blast_energy
                        {set "already_blasted" 1}
                        {if rand %blast_rand_contusion
                            {delay 0.5
                                {set "already_blasted" 0}
                            }
                            ;{con "%blast_energy"}
                            {damage_report "body" "component/shock"}
                            {chassis_work 0}
                            {tags add "stopped1"}
                            
                            {if work "turret"
                                {ik_enable "turret" 0}
                                {tags add "turr_jummed1"}
                            }
                            {weapon_work "gun" 0}{weapon_work "gun2" 0}{weapon_work "mgun" 0}{weapon_work "mgun1" 0}{weapon_work "mgun2" 0}{weapon_work "mgun3" 0}
							{stunned 1}
                            {delay %blast_crew_shock_time
                                {if not tagged "gun_brake"
                                    {weapon_work "gun" 1}
                                }
                                {weapon_work "gun2" 1}{weapon_work "mgun" 1}{weapon_work "mgun1" 1}{weapon_work "mgun2" 1}{weapon_work "mgun3" 1}
								{stunned 0}
                                {if tagged "stopped1"
                                    {tags remove "stopped1"}
                                    {if work "mover"
                                        {if not tagged "engine_brake"
                                            {chassis_work 1}
                                        }
                                    }
                                }
                                {if tagged "turr_jummed1"
                                        {if tagged "turret_brake"
                                            {tags remove "turr_jummed1"}
                                            
                                        else tagged "turret_stopped_by_body"
                                            {tags remove "turr_jummed1"}
                                        else
                                            {tags remove "turr_jummed1"}
                                            {ik_enable "turret" 1}
                                        }
                                }
                            }
                        else
                            {delay 0.5
                                {set "already_blasted" 0}
                            }
                        }
                    }
                }
            }
        }
        
    )
;MEGA BUILDING END =============================================================================================================================================================================

    {on repair
	    {if component "turret"
    		{view stop "smoke3"}
            {call "update_turret"}
            {tags remove "turret_brake"}
        else component "body"
            {view stop "smoke4"}
            {call "update_turret"}
            {tags remove "turret_stopped_by_body"}
            {tags remove "body_brake"}
            {able "select" 1}
        else component "engine"
            {tags remove "engine_brake"}
        }
    }
	{on "update_turret"
		{if work "turret"
			{if work "body"
				{ik_enable "turret" 1}
			 else
				{ik_enable "turret" 0}
			}
		 else
			{ik_enable "turret" 0}
		}
    }
}; end of "tank"


{"opened tank"
        {on "explosive_broken" overload
                {call "explosion"}
        }
}

{"m4a3c"
        {on fire "gun2"
                {spawn "startsmoke_cali"}
        }
}

{"m4a4_tulip"
        {on fire "gun2"
                {spawn "startsmoke_cali"}
        }
}

{"bm_8_24"
        {on fire "gun"
                {spawn "startsmoke_cali"}
        }
}

{"m4calliope"	; must be placed before	the props "turret"
	{on break_armor             
		{if volume "guns"           
			{call "tear_guns"}
		}
	}
	{on break_armor_again
		{if volume "guns"           
			{call "tear_guns"}
		}
	}
	{on "tear_turret"
		{if "roof_broken"
			{bone cut "gun"}
		else
			{call "tear_gun"}
		}
	}
	{on "tear_guns"
		{if not "roof_broken"
			{weapon_work "gun2" 0}
			{set "roof_broken" 1}
			{components "guns" destroy}
			{delay 0.5
				{bone cut "gun2"}
			}
			{delay_ex 0
				(define "teargun"
					{tear "piece_large_steel" bone "%gun"
						{impulse up 5 2.3 dir 3 1.5 cx 5 2 cy 5 2 rnd_dir 10 no_position}
						{add_view "smoke_black" "smoke" "basis"}
						{view start "smoke"}
						{delay_effect 20 5 "pause"}
					}
				)
				("teargun" gun(guns1))
				("teargun" gun(guns2))
				("teargun" gun(guns3))
				("teargun" gun(guns4))
				("teargun" gun(guns5))
				("teargun" gun(gun2))
			}
		}
	}
}

{"turret"
	{on spawn
		{call "update_turret"}
	}
	{on "turret_break" overload
		{components "turret" break}
	}
	{on break
		{if component "turret"
			{if not user_control
				{if rand 0.5 {kill_crew "gunner"}}
				{if rand 0.5 {kill_crew "charger"}}
				{if rand 0.5 {kill_crew "commander"}}
			}
			{call "update_turret"}
			{spawn "tank_die_particle" "Turret"}
			{spawn "circledust_norm" "Turret"}
;			{ani_play "open" -1.0 resume}
			{view start "smoke3"}
            {delay 10
    			{view stop "smoke3"}
    			{set "smoke3" 0}
            }
        else component "body"
			{spawn "circledust_norm" "Turret"}
			{call "update_turret"}
		}
	}
	{on "tear_turret"
		{if not "turret_teared"
			{set "turret_teared" 1}
			{components "turret" destroy}
			{call "mp_destroy"}
			{add_view "smoke_black_big5" "smoke_turret" "basis"}
			{view start "smoke_turret"}
			{delay 60 15
				{view stop "smoke_turret"}
			}
			{delay_ex 0
				{tear "piece_large_steel" bone "turret" id "turret"
					{impulse dir 0.5 1}
					{if rand 0.2
						{add_view "smoke_dead_norm" "smoke" "basis"}
					else
						{add_view "smoke_black" "smoke" "basis"}
					}
					{view start "smoke"}
					{delay_effect 30 5 "pause"}
					{delay 0.1
						{volumes "gun" disable obstacle}
					}
				}
			}
		}
	}
	{on "slice_load"
		{if name "turret"
			{with_effector
				{add_view "smoke_black" "smoke" "basis"}
			}
		}
	}

	{on "cut_parts"
		{if "turret_teared"
			{bone cut "turret"}
		else
                    {call "tear_turret"}
		}
	}
}

{"light tank turret"
	{on bullet_hit
		{if volume "turret"
			{if stuff "big shell fg"
				{if rand 0.8
					{call "tear_turret"}
				}
			}
		}
	}
}

{"light_turret" ; turret for btr, car, ...
	{on bullet_hit
		{if volume "turret"
			{if stuff "shell"
				{call "tear_turret"}
			}
		}
	}
}

{"armored_car"
	{on blast_hit
		{if min_energy 8
			{impulse up 2 0.5 dir 1 0.2}
		 else min_energy 1
			{impulse up 0.4 0.2 dir 0.4 0.2}
		 else min_energy 0.4
		 	{ani_play "hit"}
		}
	}
	{on "_explosion"
		{blastwave c4 3 r0 2.5 r1 10}
		{impulse up 0.7 0.3 dir 0.2 0.1}
	}

(include "tank/tank_armoredcar.inc")

}

{"light tank"
	{on blast_hit
		{if min_energy 30
			{impulse up 3 0.1 dir 6 0.1}
			{if volume "turret"
				{call "tear_turret"}
			}
		else min_energy  9
			{impulse up 0.5 0.2 dir 1 0.2}
			{call "tear_turret"}
		 else min_energy 6
			{impulse up 0.4 0.1 dir 0.7 0.2}
			{if rand 0.6 {call "tear_turret"}}
		 else min_energy 1
		 	{ani_play "hit"}
		}
	}
	{on "_explosion"
		{blastwave c4 5 r0 2.5 r1 10}
		{impulse up 0.5}
	}
(include "tank/tank_light.inc")
}

{"medium tank"
	{inflammation_time 30}
	{on blast_hit
		{if min_energy 30
			{impulse up 2.5 0.1 dir 4 0.1}
			{if volume "turret"
				{if rand 0.8
					{call "tear_turret"}
				}
			}
		else min_energy 12
			{impulse up 0.7 0.2 dir 1.5 0.2}
			{if volume "turret"
				{if rand 0.5
					{call "tear_turret"}
				}
			}
		 else min_energy 9
			{impulse up 0.3 0.2 dir 1 0.2}
		 else min_energy 7
			{impulse up 0.3 0.1 dir 0.4 0.1}
		 else min_energy 1
		 	;{ani_play "hit"}
		}
	}
	{on "_explosion"
		{blastwave c4 10 r0 2.5 r1 10}
		{impulse up 2 0.5 dir 0.4 0.2}
	}
	{on "check_water_level" overload
		{if water_level 1.6
			{able "sinking" 1}
		}
	}
(include "tank/tank_medium.inc")
}

{"heavy tank"
	{inflammation_time 35}
	{on blast_hit
		{if min_energy 30
			{impulse up 1.5 0.1 dir 2.5 0.1}
			{if volume "turret"
				{if rand 0.5
					{call "tear_turret"}
				}
			}
		else min_energy 14
			{impulse up 0.25 0.1 dir 0.35 0.1}
			{if volume "turret"
				{if rand 0.3
					{call "tear_turret"}
				}
			}
		 else min_energy 8
			{impulse up 0.2 0.1 dir 0.3 0.1}
		 else min_energy 3
		 	;{ani_play "hit"}
		}
	}
	{on "_explosion"
        {blastwave c4 15 r0 2.5 r1 10}
		{impulse up 1 1 dir 0.2 0.2}
	}
	{on "check_water_level" overload
		{if water_level 1.8
			{able "sinking" 1}
		}
	}
(include "tank/tank_heavy.inc")
}

{"mine_exploder"
	{on spawn
		{bone hide "wheel_work"}
		{add_view "dustrun_sand_big"	"wheel_work_dust"	"FXWheel_Work1"}
		{add_view "dustrun_sand_big"	"wheel_work_dust"	"FXWheel_Work2"}
		{volumes "wheel_work" disable all}
		{ani_play "wheel_stop"}
	}
	{on move on
		{bone hide "wheel"}
		{bone show "wheel_work"}
		{view start "wheel_work_dust"}
		{volumes "wheel_work" enable all}
		{volumes "wheel" disable all}
	}
	{on move off
		{bone hide "wheel_work"}
		{bone show "wheel"}
		{ani_play "wheel_stop"}
		{view pause "wheel_work_dust"}
		{volumes "wheel_work" disable all}
		{volumes "wheel" enable all}
	}
	{on blast overload
		{if not volume "wheel_work"
			{inherited}
		else
			{ani_play "explosion"}
		}
	}
}

{"pz1b tank"
	{on spawn
		{add_view	"flash_gun_big_vehicle"	"flashbarrel00"	"shooter00"	}
		{add_view	"flash_gun_big_vehicle"	"flashbarrel01"	"shooter01"	}
		{link_sound "move"				"vehicle/tracks/pz1"	}
		{link_sound "engine"			"vehicle/engine/pz1"	}
		{link_sound "engine_end"		"vehicle/engine/pz1_end"}
		{link_sound "rotate_turret" 	"vehicle/turret/light1"	}
		{link_sound "exhaust"			"vehicle/engine/pz1_up"	}
	}
	{on fire "mgun" overload
		{if  name "00"
			{view start "flashbarrel00"}
		else name "01"
			{view start "flashbarrel01"}
		}
	}
	("burn_by_engine" args 0.3)
}
(define "pz1_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/pz1"}
		{link_sound "engine"			"vehicle/engine/pz1"		}
		{link_sound "engine_end"		"vehicle/engine/pz1_end"	}
		{link_sound "exhaust"			"vehicle/engine/pz1_up"	}
	}
)
{"pz1 tank"
	("pz1_sound")
	("burn_by_engine" args 0.3)
}
{"pz1b tank"
	("pz1_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz303 tank"
	{on "add_movement_sound" overload
		{link_sound "move"			"vehicle/engine/dodge_move_new"	}
		{link_sound "engine"			"vehicle/wheels/valami"	}
		{link_sound "engine_end"		"vehicle/engine/pz1_end"}
		{link_sound "exhaust"			"vehicle/engine/Dodge_end"}
	}
	{on fire "charge"
		{call "explosion"}
	}
	{on "explosion"
		{delete}
	}
	("burn_by_engine" args 0.3)
}
(define "t26_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/bt"			}
		{link_sound "rotate_turret" 	"vehicle/turret/light"		}
		{link_sound "engine"			"vehicle/engine/t26"		}
		{link_sound "engine_end"		"vehicle/engine/t26_end"	}
		{link_sound "exhaust"			"vehicle/engine/t26_up"	}
	}
)
(define "lt_turret_sound"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/light"		}
	}
)
{"t26 tank"
	("t26_sound")
	("burn_by_engine" args 0.3)
}
(define "su76_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/t-70"}
		{link_sound "engine"			"vehicle/engine/t26"		}
		{link_sound "engine_end"		"vehicle/engine/bt_end"	}
		{link_sound "exhaust"			"vehicle/engine/bt_up"	}
	}
)
{"su76 tank"
	("su76_sound")
	("burn_by_engine" args 0.3)
}
{"zis_30 tank"
	("su76_sound")
	("burn_by_engine" args 0.3)
}
{"t20 tank"
	("su76_sound")
	("burn_by_engine" args 0.3)
}
(define "t70_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/t-70"}
		{link_sound "rotate_turret" 	"vehicle/turret/light"		}
		{link_sound "engine"			"vehicle/engine/t26"		}
		{link_sound "engine_end"		"vehicle/engine/bt_end"	}
		{link_sound "exhaust"			"vehicle/engine/bt_up"	}
	}
)
{"t70 tank"
	("t70_sound")
	("burn_by_engine" args 0.3)
}
{"t60 tank"
	("t70_sound")
	("burn_by_engine" args 0.3)
}
{"bm_8_24 tank"
	("t70_sound")
	("burn_by_engine" args 0.3)
}
{"zsu37 tank"
	("t70_sound")
	("burn_by_engine" args 0.3)
}
{"bt7a tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/bt"		}
		{link_sound "engine"			"vehicle/engine/bt"		}
		{link_sound "engine_end"		"vehicle/engine/bt_end"	}
		{link_sound "exhaust"			"vehicle/engine/bt_up"	}
		{link_sound "rotate_turret" 	"vehicle/turret/light"	}
	}
	("burn_by_engine" args 0.3)
}

(define "kv_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/is"}
		{link_sound "rotate_turret" 	"vehicle/turret/heavy"	}
		{link_sound "engine"			"vehicle/engine/kv"			}
		{link_sound "engine_end"		"vehicle/engine/kv_end"		}
		{link_sound "exhaust"			"vehicle/engine/m4a2_up"		}
	}
)
(define "is_sound"
	{on "add_movement_sound" overload
		{link_sound "move"			"vehicle/tracks/is"		}
		{link_sound "rotate_turret" 		"vehicle/turret/heavy1"		}
		{link_sound "engine"			"vehicle/engine/is"		}
		{link_sound "engine_end"		"vehicle/engine/is_end"		}
		{link_sound "exhaust"			"vehicle/engine/m4a2_up"	}
	}
)
{"kv1 tank"
	("kv_sound")
	("burn_by_engine" args 0.3)
}
{"kv2 tank"
	("kv_sound")
	("burn_by_engine" args 0.3)
}
{"kv85 tank"
	("kv_sound")
	("burn_by_engine" args 0.3)
}
{"is1 tank"
	("is_sound")
	("burn_by_engine" args 0.3)
}
{"is2 tank"
	("is_sound")
	{on "gunner_hatch_open" overload
		{ani_play "open2"}
	}
	("burn_by_engine" args 0.3)
}
{"is3 tank"
	("is_sound")
	("burn_by_engine" args 0.3)
}
{"m26_pershing tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/m26"	}
		{link_sound "rotate_turret" 	"vehicle/turret/pershing"		}
		{link_sound "engine"			"vehicle/engine/m26"		}
		{link_sound "engine_end"		"vehicle/engine/m4a2_end"	}
		{link_sound "exhaust"			"vehicle/engine/m4a2_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"m26e4 tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/m26"	}
		{link_sound "rotate_turret" 	"vehicle/turret/pershing"		}
		{link_sound "engine"			"vehicle/engine/m26"		}
		{link_sound "engine_end"		"vehicle/engine/m4a2_end"	}
		{link_sound "exhaust"			"vehicle/engine/m4a2_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"isu152 tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/is"		}
		{link_sound "engine"			"vehicle/engine/isu"		}
		{link_sound "engine_end"		"vehicle/engine/isu_end"	}
		{link_sound "exhaust"			"vehicle/engine/m4a2_up"		}
	}
	{on "gunner_hatch_open" overload
		{ani_play "open2"}
	}
	("burn_by_engine" args 0.3)
}
{"isu122 tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/is"		}
		{link_sound "engine"			"vehicle/engine/isu"		}
		{link_sound "engine_end"		"vehicle/engine/isu_end"	}
		{link_sound "exhaust"			"vehicle/engine/m4a2_up"		}
	}
	("burn_by_engine" args 0.3)
}
(define "t34_sound"
	{on "add_movement_sound" overload
		{link_sound "move"			"vehicle/tracks/t34"	}
		{link_sound "rotate_turret" 	"vehicle/turret/medium"		}
		{link_sound "engine"			"vehicle/engine/t34"		}
		{link_sound "engine_end"		"vehicle/engine/t34_end"	}
		{link_sound "exhaust"			"vehicle/engine/m3a1_up"		}
	}
)
{"t34_0 tank"
	("t34_sound")
	("burn_by_engine" args 0.3)
}
{"t34_1 tank"
	("t34_sound")
	("burn_by_engine" args 0.3)
}
{"t34_2 tank"
	("t34_sound")
	("burn_by_engine" args 0.3)
}
{"su85 tank"
	("t34_sound")
	("burn_by_engine" args 0.3)
}
{"su122 tank"
	("t34_sound")
	("burn_by_engine" args 0.3)
}
{"su100 tank"
	("t34_sound")
	("burn_by_engine" args 0.3)
}
{"t34_3 tank"
	{on "add_movement_sound" overload
		{link_sound "move"			"vehicle/tracks/t34"	}
		{link_sound "rotate_turret" 	"vehicle/turret/t34"		}
		{link_sound "engine"			"vehicle/engine/t3485"		}
		{link_sound "engine_end"		"vehicle/engine/t3485_end"	}
		{link_sound "exhaust"			"vehicle/engine/m3a1_up"	}
	}
	("burn_by_engine" args 0.3)
}
(define "pz5g_sound"
	{on "add_movement_sound" overload
		{link_sound "move"			"vehicle/tracks/jugdpanther"		}
		{link_sound "engine"			"vehicle/engine/jugdpanther"		}
		{link_sound "engine_end"		"vehicle/engine/jugdpanther_end"	}
		{link_sound "rotate_turret" 		"vehicle/turret/heavy"	}
		{link_sound "exhaust"			"vehicle/engine/jugdpanther_up"	}
	}
)
(define "ho-ri_sound"
	{on "add_movement_sound" overload
		{link_sound "move"			"vehicle/tracks/is"		}
		{link_sound "engine"			"vehicle/engine/jugdpanther"		}
		{link_sound "engine_end"		"vehicle/engine/jugdpanther_end"	}
		{link_sound "rotate_turret" 		"vehicle/turret/heavy"	}
		{link_sound "exhaust"			"vehicle/engine/jugdpanther_up"	}
	}
)

{"pz5g tank"
	("pz5g_sound")
	("burn_by_engine" args 0.3)
}

{"jugdpanther tank"
	("pz5g_sound")
	("burn_by_engine" args 0.3)
}

{"ho-ri tank"
	("ho-ri_sound")
	("burn_by_engine" args 0.3)
}

{"ho-ri_1 tank"
	("ho-ri_sound")
	("burn_by_engine" args 0.3)
}

{"chi-ri tank"
	("ho-ri_sound")
	("burn_by_engine" args 0.3)
}

(define "m8_sound"
	{on "add_movement_sound" overload
		{link_sound "move"			"vehicle/wheels/m8grayhound"		}
		{link_sound "engine"			"vehicle/engine/m8grayhound"		}
		{link_sound "engine_end"		"vehicle/engine/m8grayhound_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/light"	}
		{link_sound "exhaust"			"vehicle/engine/m8grayhound_up" 	}
	}
)
{"m8 tank"
	;("m8_sound")
	("burn_by_engine" args 0.3)
}
{"m3stuart tank"
	("m8_sound")
	("burn_by_engine" args 0.3)
}
{"mk2 tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/mk2"	}
		{link_sound "engine"			"vehicle/engine/pz2"		}
		{link_sound "engine_end"		"vehicle/engine/pz2_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/medium1"		}
		{link_sound "exhaust"			"vehicle/engine/pz2_up" 	}
	}
	("burn_by_engine" args 0.3)
}
(define "mk7_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/mk7"	}
		{link_sound "engine"			"vehicle/engine/mk7"		}
		{link_sound "engine_end"		"vehicle/engine/mk7_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/mk7_turret"		}
		{link_sound "exhaust"			"vehicle/engine/mk7_up" 	}
	}
)
{"mk7 tank"
	("mk7_sound")
	("burn_by_engine" args 0.3)
}
{"mk2a tank"
	("mk7_sound")
	("burn_by_engine" args 0.3)
}
{"universal_carrier tank"
	("mk7_sound")
	("burn_by_engine" args 0.3)
}
(define "bishop_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/bishop"	}
		{link_sound "engine"			"vehicle/engine/bishop"		}
		{link_sound "engine_end"		"vehicle/engine/bishop_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/medium1"		}
		{link_sound "exhaust"			"vehicle/engine/bishop_up" 	}
	}
)
{"bishop tank"
	("bishop_sound")
	("burn_by_engine" args 0.3)
}
{"mk3 tank"
	("bishop_sound")
	("burn_by_engine" args 0.3)
}
(define "mk6_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/crusader"	}
		{link_sound "engine"			"vehicle/engine/crusader"		}
		{link_sound "engine_end"		"vehicle/engine/crusader_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/medium1"		}
		{link_sound "exhaust"			"vehicle/engine/crusader_up" 	}
	}
)
{"mk6 tank"
	("mk6_sound")
	("burn_by_engine" args 0.3)
}
{"crusaderaa1 tank"
	("mk6_sound")
	("burn_by_engine" args 0.3)
}
{"crusaderaa2 tank"
	("mk6_sound")
	("burn_by_engine" args 0.3)
}
{"mk4 tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/churchill"		}
		{link_sound "engine"			"vehicle/engine/churchill"		}
		{link_sound "engine_end"		"vehicle/engine/churchill_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/churchill_turret"	}
		{link_sound "exhaust"			"vehicle/engine/churchill_up" 	}
	}
	("burn_by_engine" args 0.3)
}
{"cromwell_mk_vi tank"
	{on "add_movement_sound" overload
		{link_sound "move"		    	"vehicle/tracks/cromwell"	}
		{link_sound "engine"			"vehicle/engine/cromwell"		}
		{link_sound "engine_end"		"vehicle/engine/cromwell_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/churchill_turret"	}
		{link_sound "exhaust"			"vehicle/engine/cromwell_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"cromwell_mk_vii tank"
	{on "add_movement_sound" overload
		{link_sound "move"		    	"vehicle/tracks/cromwell"	}
		{link_sound "engine"			"vehicle/engine/cromwell"		}
		{link_sound "engine_end"		"vehicle/engine/cromwell_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/churchill_turret"	}
		{link_sound "exhaust"			"vehicle/engine/cromwell_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"m4a3m tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/m4a2"  }
		{link_sound "engine"			"vehicle/engine/m4a2"		}
		{link_sound "engine_end"		"vehicle/engine/m4a2_end"	}
		{link_sound "exhaust"			"vehicle/engine/m4a2_up"	}
		{link_sound "rotate_turret" 	"vehicle/turret/heavy"	}
	}
	("burn_by_engine" args 0.3)
}
(define "m4_sound"
	{on "add_movement_sound" overload
		{link_sound "move"					"vehicle/tracks/m4a2"			}
		{link_sound "engine"				"vehicle/engine/m4"			}
		{link_sound "engine_end"			"vehicle/engine/m4_end"		}
		{link_sound "exhaust"				"vehicle/engine/m4a2_up"		}
		{link_sound "rotate_turret"     	"vehicle/turret/sherman"   	}
	}
)
(define "m4_turret_sound"
	{on "add_movement_sound"
		{link_sound "rotate_turret"     	"vehicle/turret/sherman"   	}
	}
)
{"m4a3_75 tank"
	("m4_sound")
	("burn_by_engine" args 0.3)
}
{"m4a4 tank"
	("m4_sound")
	("burn_by_engine" args 0.3)
}
{"m4a4_tulip tank"
	("m4_sound")
	("burn_by_engine" args 0.3)
}
{"m4a3_105 tank"
	("m4_sound")
	("burn_by_engine" args 0.3)
}
{"m4a3e8 tank"
	("m4_sound")
	("burn_by_engine" args 0.3)
}
{"m4a3c tank"
	("m4_sound")
	("burn_by_engine" args 0.3)
}
{"m12gmc tank"
	("m4_sound")
	("burn_by_engine" args 0.3)
}
{"m4a4_firefly tank"
	{on "add_movement_sound" overload
		{link_sound "move"					"vehicle/tracks/m4a2"		}
		{link_sound "engine"				"vehicle/engine/m4"		}
		{link_sound "engine_end"			"vehicle/engine/m4_end"	}
		{link_sound "exhaust"				"vehicle/engine/m4a2_up"	}
		{link_sound "rotate_turret" 	    "vehicle/turret/sherman"	}
	}
	("burn_by_engine" args 0.3)
}
{"m4a3e2_jumbo tank"
	{on "add_movement_sound" overload
		{link_sound "move"					"vehicle/tracks/m4a2"		}
		{link_sound "engine"				"vehicle/engine/m4"		}
		{link_sound "engine_end"			"vehicle/engine/m4_end"	}
		{link_sound "exhaust"				"vehicle/engine/m4a2_up"	}
		{link_sound "rotate_turret" 	    "vehicle/turret/sherman"	}
	}
	("burn_by_engine" args 0.3)
}
{"m4a3e2_jumbo_76 tank"
	{on "add_movement_sound" overload
		{link_sound "move"					"vehicle/tracks/m4a2"		}
		{link_sound "engine"				"vehicle/engine/m4"		}
		{link_sound "engine_end"			"vehicle/engine/m4_end"	}
		{link_sound "exhaust"				"vehicle/engine/m4a2_up"	}
		{link_sound "rotate_turret" 	    "vehicle/turret/sherman"	}
	}
	("burn_by_engine" args 0.3)
}
{"lvt4 tank"
	("m4_sound")
	("burn_by_engine" args 0.3)
}
(define "m7_sound"
	{on "add_movement_sound" overload
		{link_sound "move"					"vehicle/tracks/m7"		}
		{link_sound "engine"				"vehicle/engine/m7"		}
		{link_sound "engine_end"			"vehicle/engine/m7_end"	}
		{link_sound "exhaust"				"vehicle/engine/m4a2_up"	}
		{link_sound "rotate_turret" 	    "vehicle/turret/sherman"	}
	}
)
{"m7 tank"
	("m7_sound")
	("burn_by_engine" args 0.3)
}
{"m7_eng tank"
	("m7_sound")
	("burn_by_engine" args 0.3)
}
{"m19 tank"
	("m7_sound")
	("burn_by_engine" args 0.3)
}
{"m8 tank"
	("m7_sound")
	("burn_by_engine" args 0.3)
}
{"jagdpanther tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/jugdpanther"  		}
		{link_sound "engine"			"vehicle/engine/jugdpanther"		}
		{link_sound "engine_end"		"vehicle/engine/jugdpanther_end"	}
		{link_sound "exhaust"			"vehicle/engine/jugdpanther_up" 	}
		{link_sound "rotate_turret" 	"vehicle/turret/heavy1"	}
	}
	("burn_by_engine" args 0.3)
}
(define "pz6_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/pz6"	}
		{link_sound "engine"			"vehicle/engine/pz6"		}
		{link_sound "engine_end"		"vehicle/engine/pz6_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/pz6"	}
		{link_sound "exhaust"			"vehicle/engine/pz6_up"	}
	}
)
{"pz6bh tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/jugdpanther"	}
		{link_sound "engine"			"vehicle/engine/jagdtiger"		}
		{link_sound "engine_end"		"vehicle/engine/jagdtiger_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/pz6"	}
		{link_sound "exhaust"			"vehicle/engine/pz6_up"	}
	}
	{on "gunner_hatch_open" overload
		{ani_play "open2"}
	}
	("burn_by_engine" args 0.3)
}
{"pz6e tank"
	("pz6_sound")
	{on "gunner_hatch_open" overload
		{ani_play "open2"}
	}
	("burn_by_engine" args 0.3)
}
{"veteran_tiger tank"
	("pz6_sound")
	{on "gunner_hatch_open" overload
		{ani_play "open" -1.0 resume}
		{ani_play "open2"}
	}
	("burn_by_engine" args 0.3)
}
{"elefant tank"
	("pz6_sound")
	("burn_by_engine" args 0.3)
}
{"jagdtiger tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/jugdpanther"	}
		{link_sound "engine"			"vehicle/engine/jagdtiger"		}
		{link_sound "engine_end"		"vehicle/engine/jagdtiger_end"	}
		{link_sound "exhaust"			"vehicle/engine/pz6_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"hetzer tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/hetzer"	}
		{link_sound "engine"			"vehicle/engine/hetzer"		}
		{link_sound "engine_end"		"vehicle/engine/hetzer_end"	}
		{link_sound "exhaust"			"vehicle/engine/hetzer_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"ba64 tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/wheels/wheels"	}
		{link_sound "engine"			"vehicle/engine/ba11"		}
		{link_sound "engine_end"		"vehicle/engine/ba11_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/light1"	}
		{link_sound "exhaust"			"vehicle/engine/ba11_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"pz2l tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/pz2"	}
		{link_sound "engine"			"vehicle/engine/pz2"		}
		{link_sound "engine_end"		"vehicle/engine/pz2_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/light1"	}
		{link_sound "exhaust"			"vehicle/engine/pz2_up" 	}
	}
	("burn_by_engine" args 0.3)
}
{"pz2f tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/pz2"	}
		{link_sound "engine"			"vehicle/engine/pz2"		}
		{link_sound "engine_end"		"vehicle/engine/pz2_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/light1"	}
		{link_sound "exhaust"			"vehicle/engine/pz2_up" 	}
	}
	("burn_by_engine" args 0.3)
}
(define "pz3_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/pz3"	}
		{link_sound "engine"			"vehicle/engine/pz3"		}
		{link_sound "engine_end"		"vehicle/engine/pz3_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/heavy1"	}
		{link_sound "exhaust"			"vehicle/engine/pz3_up"	}
	}
)
{"steyr_rso tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/pz2"	}
		{link_sound "engine"			"vehicle/engine/pz1"		}
		{link_sound "engine_end"		"vehicle/engine/pz2_end"	}
		{link_sound "exhaust"			"vehicle/engine/pz2_up" 	}
	}
	("burn_by_engine" args 0.3)
}
{"pz3f tank"
	("pz3_sound")
	("burn_by_engine" args 0.3)
}
{"pz3 tank"
	("pz3_sound")
	("burn_by_engine" args 0.3)
}
{"pz3n tank"
	("pz3_sound")
	("burn_by_engine" args 0.3)
}
{"stug3g tank"
	("pz3_sound")
	{on "gunner_hatch_open" overload
		{ani_play "open" -1.0 resume}
	}
	("burn_by_engine" args 0.3)
}
{"stuh42 tank"
	("pz3_sound")
	{on "gunner_hatch_open" overload
		{ani_play "open2"}
	}
	("burn_by_engine" args 0.3)
}
{"pz3m tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/pz3"	}
		{link_sound "engine"			"vehicle/engine/pz3"		}
		{link_sound "engine_end"		"vehicle/engine/pz3_end"	}
		{link_sound "exhaust"			"vehicle/engine/pz3_up" 	}
	}
	("burn_by_engine" args 0.3)
}
(define "pz4_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/pz4"	}
		{link_sound "engine"			"vehicle/engine/pz4"		}
		{link_sound "engine_end"		"vehicle/engine/pz4_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/heavy1"	}
		{link_sound "exhaust"			"vehicle/engine/pz4_up"	  	}
	}
)
(define "wespe_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/pz3"	}
		{link_sound "engine"			"vehicle/engine/hetzer"		}
		{link_sound "engine_end"		"vehicle/engine/pz2_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/heavy1"	}
		{link_sound "exhaust"			"vehicle/engine/pz2_up"	  	}
	}
)
{"wespe tank"
	("wespe_sound")
	("burn_by_engine" args 0.3)
}
{"marder_3h tank"
	("wespe_sound")
	("burn_by_engine" args 0.3)
}
{"pz4d tank"
	("pz4_sound")
	("burn_by_engine" args 0.3)
}
{"jagdpanzer_iv tank"
	("pz4_sound")
	("burn_by_engine" args 0.3)
}
{"welberwind tank"
	("pz4_sound")
	("burn_by_engine" args 0.3)
}
{"ostwind tank"
	("pz4_sound")
	("burn_by_engine" args 0.3)
}
{"pz4g tank"
	("pz4_sound")
	("burn_by_engine" args 0.3)
}
{"pz4h tank"
	("pz4_sound")
	("burn_by_engine" args 0.3)
}
{"hummel tank"
	("pz4_sound")
	("burn_by_engine" args 0.3)
}
{"nashorn tank"
	("pz4_sound")
	("burn_by_engine" args 0.3)
}
(define "sdkfz_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/wheels/wheels"			}
		{link_sound "engine"			"vehicle/engine/sdkfz232"		}
		{link_sound "engine_end"		"vehicle/engine/sdkfz232_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/light1"			}
		{link_sound "exhaust"			"vehicle/engine/sdkfz232_up"	}
	}
)
{"sdkfz222 tank"
	("sdkfz_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz223 tank"
	("sdkfz_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz232 tank"
	("sdkfz_sound")
	("burn_by_engine" args 0.3)
}
(define "sdkfz234_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/sdkfz234"		}
		{link_sound "engine"			"vehicle/engine/sdkfz234"		}
		{link_sound "engine_end"		"vehicle/engine/sdkfz234_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/heavy1"			}
		{link_sound "exhaust"			"vehicle/engine/sdkfz234_up"	}
	}
)
{"sdkfz234 tank"
	("sdkfz234_sound")
	("burn_by_engine" args 0.3)
}
{"ba11 tank"
	("sdkfz234_sound")
	("burn_by_engine" args 0.3)
}
{"type93scout tank"
	("sdkfz234_sound")
	("burn_by_engine" args 0.3)
}
(define "m8grayhound_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/wheels/m8grayhound"	}
		{link_sound "engine"			"vehicle/engine/m8grayhound"		}
		{link_sound "engine_end"		"vehicle/engine/m8grayhound_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/light1"	}
		{link_sound "exhaust"			"vehicle/engine/m8grayhound_up"	}
	}
)
{"m8grayhound tank"
	("m8grayhound_sound")
	{on "gunner_hatch_open" overload
		{ani_play "open" -1.0 resume}
	}
	("burn_by_engine" args 0.3)
}
{"m20 tank"
	("m8grayhound_sound")
	("burn_by_engine" args 0.3)
}
{"mk2daimler"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/wheels/wheels"			}
		{link_sound "engine"			"vehicle/engine/sdkfz234"		}
		{link_sound "engine_end"		"vehicle/engine/sdkfz234_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/light1"			}
		{link_sound "exhaust"			"vehicle/engine/sdkfz234_up"	}
	}
	("burn_by_engine" args 0.3)
}
(define "hanomag_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/sdkfz251"	}
		{link_sound "engine"			"vehicle/engine/sdkfz251"	}
		{link_sound "engine_end"		"vehicle/engine/sdkfz251_end"}
		{link_sound "rotate_turret" 	"vehicle/turret/light1"		}
		{link_sound "exhaust"			"vehicle/engine/sdkfz251_up"	}
	}
)
{"sdkfz4 tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/sdkfz10"	 }
		{link_sound "engine"			"vehicle/engine/sdkfz250"	 }
		{link_sound "engine_end"		"vehicle/engine/sdkfz250_end"}
		{link_sound "rotate_turret" 	"vehicle/turret/light"		 }
		{link_sound "exhaust"			"vehicle/engine/sdkfz250_up" }
	}
	("burn_by_engine" args 0.3)
}
{"sdkfz251_1 tank"
	("hanomag_sound")
	("burn_by_engine" args 0.3)
}
{"ho-ha3mgun tank"
	("hanomag_sound")
	("burn_by_engine" args 0.3)
}
(define "m3_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/m3a1"	}
		{link_sound "engine"			"vehicle/engine/m3a1"		}
		{link_sound "engine_end"		"vehicle/engine/m3a1_end"	}
;		{link_sound "rotate_turret" 	"vehicle/turret/light"	}
		{link_sound "exhaust"			"vehicle/engine/m3a1_up"	}
	}
)
{"m3 tank"
	("m3_sound")
	("burn_by_engine" args 0.3)
}
{"m3_usa tank"
	("m3_sound")
	("burn_by_engine" args 0.3)
}
{"m3_eng tank"
	("m3_sound")
	("burn_by_engine" args 0.3)
}
{"m16 tank"
	("m3_sound")
	("burn_by_engine" args 0.3)
}
{"grant_m3 tank"
	("m4_sound")
	("burn_by_engine" args 0.3)
}
(define "cometa34_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/kv"	}
		{link_sound "engine"			"vehicle/engine/m7"		}
		{link_sound "engine_end"		"vehicle/engine/m7_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/t34"	}
		{link_sound "exhaust"			"vehicle/engine/t26_up"	}
	}
)
{"cometa34 tank"
	("cometa34_sound")
	("burn_by_engine" args 0.3)
}
{"centurion tank"
	("cometa34_sound")
	("burn_by_engine" args 0.3)
}
(define "m10wolverine_sound"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/mk2"	}
		{link_sound "engine"			"vehicle/engine/m10wolverine"		}
		{link_sound "engine_end"		"vehicle/engine/m4_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/sherman"	}
		{link_sound "exhaust"			"vehicle/engine/m4a2_up"	}
	}
)
{"m10wolverine tank"
	("m10wolverine_sound")
	{on "gunner_hatch_open" overload
		{ani_play "open" -1.0 resume}
	}
	("burn_by_engine" args 0.3)
}
{"m36 tank"
	("m10wolverine_sound")
	{on "gunner_hatch_open" overload
		{ani_play "open" -1.0 resume}
	}
	("burn_by_engine" args 0.3)
}
{"m18 tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/mk2"	}
		{link_sound "engine"			"vehicle/engine/m18hellcat"		}
		{link_sound "engine_end"		"vehicle/engine/m4_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/sherman"	}
		{link_sound "exhaust"			"vehicle/engine/m4a2_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"achilles tank"
	("m10wolverine_sound")
	{on "gunner_hatch_open" overload
		{ani_play "open" -1.0 resume}
	}
	("burn_by_engine" args 0.3)
}
{"archer tank"
	("bishop_sound")
	("burn_by_engine" args 0.3)
}
{"203b4 tank"
	("bishop_sound")
	("burn_by_engine" args 0.3)
}
{"m24 tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/m3stuart"	}
		{link_sound "engine"			"vehicle/engine/m18hellcat"		}
		{link_sound "engine_end"		"vehicle/engine/m4_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/sherman"	}
		{link_sound "exhaust"			"vehicle/engine/m4a2_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"m5a1 tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/m3stuart"	}
		{link_sound "engine"			"vehicle/engine/m3stuart"		}
		{link_sound "engine_end"		"vehicle/engine/tankengine_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/light"	}
		{link_sound "exhaust"			"vehicle/engine/tankengine_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"m4a2_76w tank"
	("m4_turret_sound")
	("burn_by_engine" args 0.3)
}
{"sturmtiger tank"
	("pz6_sound")
	("burn_by_engine" args 0.3)
	{on "_explosion"
		{spawn "fuel_die"}
		{blastwave c4 5 r0 4 r1 15}
		{fire radius 8 time 15 heating 10}
	}
	{on fire "gun"
		{spawn "sturmtiger_fire" inv_normal}
	}
	{on "__explosion"
		{set "big_explosion" 0}
		{if explosive_amount 50         
			{blastwave c4 30 r0 8 r1 16}     
			{blastwave c4 3 r0 20 r1 30}
			{spawn "train_die" "basis"}
			{set "big_explosion" 1}
		}
	}
	{on "spawn_shellhole"
		{if "big_explosion"
			{spawn "crater_extra_big" "basis" terrain_texmod}
			{spawn "shellhole_big_dead" "basis"}
		}
	}
;	{on pierce
;		{if volume "gun" 
;			{if hit_side front            
;				{if rand 0.4
;					{call "stat_break"}
;					{call "__explosion"}
;				} 
;			}
;		}
;	}
}
{"chi-ri tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/heavy2"	}
		{link_sound "move"				"vehicle/tracks/chi-ha"	}
		{link_sound "engine"			"vehicle/engine/heavy"	}
		{link_sound "engine_end"		"vehicle/engine/heavy_end"}
		{link_sound "exhaust"			"vehicle/engine/heavy_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"chi-ha120 tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/churchill_turret"	}
		{link_sound "move"				"vehicle/tracks/chi-ha"	}
		{link_sound "engine"			"vehicle/engine/chi-ha"	}
		{link_sound "engine_end"		"vehicle/engine/hetzer_end"}
		{link_sound "exhaust"			"vehicle/engine/hetzer_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"chi-ha47 tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/churchill_turret"	}
		{link_sound "move"				"vehicle/tracks/chi-ha"	}
		{link_sound "engine"			"vehicle/engine/chi-ha"	}
		{link_sound "engine_end"		"vehicle/engine/hetzer_end"}
		{link_sound "exhaust"			"vehicle/engine/hetzer_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"chi-ha57 tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/light"	}
		{link_sound "move"				"vehicle/tracks/chi-ha"	}
		{link_sound "engine"			"vehicle/engine/chi-ha"	}
		{link_sound "engine_end"		"vehicle/engine/hetzer_end"}
		{link_sound "exhaust"			"vehicle/engine/hetzer_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"ha-go tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/light"	}
		{link_sound "move"				"vehicle/tracks/pz1"	}
		{link_sound "engine"			"vehicle/engine/chi-ha"	}
		{link_sound "engine_end"		"vehicle/engine/mb_end"}
		{link_sound "exhaust"			"vehicle/engine/mb_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"ke-nu tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/light"	}
		{link_sound "move"				"vehicle/tracks/m26"	}
		{link_sound "engine"			"vehicle/engine/chi-ha"	}
		{link_sound "engine_end"		"vehicle/engine/mb_end"}
		{link_sound "exhaust"			"vehicle/engine/mb_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"chi-he tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/medium"	}
		{link_sound "move"				"vehicle/tracks/m26"	}
		{link_sound "engine"			"vehicle/engine/chi-ha"	}
		{link_sound "engine_end"		"vehicle/engine/tank_end"}
		{link_sound "exhaust"			"vehicle/engine/tank_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"chi-nu tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/medium1"	}
		{link_sound "move"				"vehicle/tracks/chi-ha"	}
		{link_sound "engine"			"vehicle/engine/chi-ha"	}
		{link_sound "engine_end"		"vehicle/engine/mb_end"}
		{link_sound "exhaust"			"vehicle/engine/mb_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"chi-to tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/medium1"	}
		{link_sound "move"				"vehicle/tracks/mk7"	}
		{link_sound "engine"			"vehicle/engine/mk7"	}
		{link_sound "engine_end"		"vehicle/engine/mk7_end"}
		{link_sound "exhaust"			"vehicle/engine/mk7_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"ho-i tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/medium3"	}
		{link_sound "move"				"vehicle/tracks/chi-ha"	}
		{link_sound "engine"			"vehicle/engine/t34"	}
		{link_sound "engine_end"		"vehicle/engine/t34_end"}
		{link_sound "exhaust"			"vehicle/engine/t34_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"ho-ni1 tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/light"	}
		{link_sound "move"				"vehicle/tracks/chi-ha"	}
		{link_sound "engine"			"vehicle/engine/chi-ha"	}
		{link_sound "engine_end"		"vehicle/engine/hetzer_end"}
		{link_sound "exhaust"			"vehicle/engine/hetzer_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"ho-ni2 tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/light"	}
		{link_sound "move"				"vehicle/tracks/chi-ha"	}
		{link_sound "engine"			"vehicle/engine/chi-ha"	}
		{link_sound "engine_end"		"vehicle/engine/hetzer_end"}
		{link_sound "exhaust"			"vehicle/engine/hetzer_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"ho-ni_3 tank"
	{on "add_movement_sound" overload
		{link_sound "rotate_turret" 	"vehicle/turret/light"	}
		{link_sound "move"				"vehicle/tracks/chi-ha"	}
		{link_sound "engine"			"vehicle/engine/chi-ha"	}
		{link_sound "engine_end"		"vehicle/engine/hetzer_end"}
		{link_sound "exhaust"			"vehicle/engine/hetzer_up"	}
	}
	("burn_by_engine" args 0.3)
}
{"churchill_avre tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/churchill"		}
		{link_sound "engine"			"vehicle/engine/churchill"		}
		{link_sound "engine_end"		"vehicle/engine/churchill_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/churchill_turret"	}
		{link_sound "exhaust"			"vehicle/engine/churchill_up" 	}
	}
	("burn_by_engine" args 0.3)
}
{"churchill_mk_vii tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/churchill"		}
		{link_sound "engine"			"vehicle/engine/churchill"		}
		{link_sound "engine_end"		"vehicle/engine/churchill_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/churchill_turret"	}
		{link_sound "exhaust"			"vehicle/engine/churchill_up" 	}
	}
	("burn_by_engine" args 0.3)
}
{"churchill_mk_vii tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/churchill"		}
		{link_sound "engine"			"vehicle/engine/churchill"		}
		{link_sound "engine_end"		"vehicle/engine/churchill_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/churchill_turret"	}
		{link_sound "exhaust"			"vehicle/engine/churchill_up" 	}
	}
	("burn_by_engine" args 0.3)
}
{"black_prince tank"
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/churchill"		}
		{link_sound "engine"			"vehicle/engine/churchill"		}
		{link_sound "engine_end"		"vehicle/engine/churchill_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/t34"	}
		{link_sound "exhaust"			"vehicle/engine/churchill_up" 	}
	}
	("burn_by_engine" args 0.3)
}
{"ss-d tank"
	{on spawn	
		{add_view "flamer_fire" "flame1" "foresight9"}
		{add_view "flamer_fire" "flame2" "foresight10"}
		{add_view "flamer_fire" "flame3" "foresight13"}
		{add_view "flamer_fire" "flame4" "foresight12"}
		{add_view "flamer_fire" "flame5" "foresight11"}
		
		{add_view "flamer_fire_barrel" "fire1" "foresight9"}
		{add_view "flamer_fire_barrel" "fire2" "foresight10"}
		{add_view "flamer_fire_barrel" "fire3" "foresight13"}
		{add_view "flamer_fire_barrel" "fire4" "foresight12"}
		{add_view "flamer_fire_barrel" "fire5" "foresight11"}
	
		{view show	"fire1"}
		{view show	"fire2"}
		{view show	"fire3"}
		{view show	"fire4"}
		{view show	"fire5"}
		
		{view start	"fire1"}
		{view start	"fire2"}
		{view start	"fire3"}
		{view start	"fire4"}
		{view start	"fire5"}
	}
	{on break_armor
		{if name "pierce"
			{if rand 0.3
				{if volume "body"
					{call "explosion"}
				}
                        }
                else name "blast"
			{if volume "body"
				{call "explosion"}
			}
                }
	}
	{on "_explosion"
		{spawn "fuel_die"}
		{blastwave c4 5 r0 4 r1 15}
		{fire radius 8 time 15 heating 10}
	}
	
	{on fire "flamer1"
		{view start	"flame1"}
		{kill_delay "fire1"}
		{delay 0.5 "fire1"
			{view pause	"flame1"}
		}
	}
	{on fire "flamer2"
		{view start	"flame2"}
		{kill_delay "fire2"}
		{delay 0.5 "fire2"
			{view pause	"flame2"}
		}
	}
	{on fire "flamer3"
		{view start	"flame3"}
		{kill_delay "fire3"}
		{delay 0.5 "fire3"
			{view pause	"flame3"}
		}
	}
	{on fire "flamer4"
		{view start	"flame4"}
		{kill_delay "fire4"}
		{delay 0.5 "fire4"
			{view pause	"flame4"}
		}
	}
	{on fire "flamer5"
		{view start	"flame5"}
		{kill_delay "fire5"}
		{delay 0.5 "fire5"
			{view pause	"flame5"}
		}
	}
		
}
{"churchill_crocodile tank"
	{on spawn
		{add_view "flamer_fire" "flame1" "foresight4"}
		{add_view "flamer_fire_barrel" "fire1" "foresight4"}
		{view show	"fire1"}

		{view start	"fire1"}
	}
	{on operatable on	
		{view start	"fire1"}
	}	
	{on operatable off		
		{view stop	"fire1"}
	}
	{on "_explosion"
		{spawn "fuel_die"}
		{blastwave c4 5 r0 4 r1 15}
		{fire radius 5 time 15 heating 10}
	}
	{on fire "flamer1"
		{view start	"flame1"}
		{kill_delay "fire1"}
		{delay 0.5 "fire1"
			{view pause	"flame1"}
		}
	}
	{on "add_movement_sound" overload
		{link_sound "move"				"vehicle/tracks/churchill"		}
		{link_sound "engine"			"vehicle/engine/churchill"		}
		{link_sound "engine_end"		"vehicle/engine/churchill_end"	}
		{link_sound "rotate_turret" 	"vehicle/turret/churchill_turret"	}
		{link_sound "exhaust"			"vehicle/engine/churchill_up" 	}
	}
	("burn_by_engine" args 0.3)	
}
{"m4a3_zippo tank"
	{on spawn
		{add_view "flamer_fire" "flame1" "foresight5"}
		{add_view "flamer_fire_barrel" "fire1" "foresight5"}
		{view show	"fire1"}

		{view start	"fire1"}
	}
	{on operatable on	
		{view start	"fire1"}
	}	
	{on operatable off		
		{view stop	"fire1"}
	}
	{on "_explosion"
		{spawn "fuel_die"}
		{blastwave c4 5 r0 4 r1 15}
		{fire radius 5 time 15 heating 10}
	}
	{on fire "flamer1"
		{view start	"flame1"}
		{kill_delay "fire1"}
		{delay 0.5 "fire1"
			{view pause	"flame1"}
		}
	}
	{on "add_movement_sound" overload
		{link_sound "move"					"vehicle/tracks/m4"			}
		{link_sound "engine"				"vehicle/engine/m4"			}
		{link_sound "engine_end"			"vehicle/engine/m4_end"		}
		{link_sound "exhaust"				"vehicle/engine/m4a2_up"		}
		{link_sound "rotate_turret"     	"vehicle/turret/sherman"   	}
	}
	("burn_by_engine" args 0.3)	
}
{"karlthor tank"
	{on "add_movement_sound" overload
		{link_sound "move"			"vehicle/tracks/karl_track"		}
		{link_sound "engine"			"vehicle/engine/karl"		}
		{link_sound "engine_end"		"vehicle/engine/karl_end"	}
		{link_sound "exhaust"			"vehicle/engine/karl_up" 	}
	}
	("burn_by_engine" args 0.3)
}
{"brummbar tank"
	("pz6_sound")
	("burn_by_engine" args 0.3)
	{on "_explosion"
		{spawn "fuel_die"}
		{blastwave c4 5 r0 4 r1 15}
		{fire radius 8 time 15 heating 10}
	}
	{on fire "gun"
		{spawn "sturmtiger_fire" inv_normal}
	}
	{on "__explosion"
		{set "big_explosion" 0}
		{if explosive_amount 50         
			{blastwave c4 30 r0 8 r1 16}     
			{blastwave c4 3 r0 20 r1 30}
			{spawn "train_die" "basis"}
			{set "big_explosion" 1}
		}
	}
	{on "spawn_shellhole"
		{if "big_explosion"
			{spawn "crater_extra_big" "basis" terrain_texmod}
			{spawn "shellhole_big_dead" "basis"}
		}
	}
}
{"sdkfz138_1 tank"
	("wespe_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz234_ger2 tank"
	("sdkfz234_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz234_1 tank"
	("sdkfz234_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz234_3 tank"
	("sdkfz234_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz234_4 tank"
	("sdkfz234_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz250_1 tank"
	("hanomag_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz250_11 tank"
	("hanomag_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz251_1_stuka tank"
	("hanomag_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz7 tank"
	("hanomag_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz7_2 tank"
	("hanomag_sound")
	("burn_by_engine" args 0.3)
}
{"sdkfz8 tank"
	("hanomag_sound")
	("burn_by_engine" args 0.3)
}
{"ot34_2 tank"
	("t34_sound")
	("burn_by_engine" args 0.2)
	{on spawn   
		{add_view "flamer_fire" "flame1" "foresight4"}
		{add_view "flamer_fire_barrel" "fire1" "foresight4"}
		{view show   "fire1"}
		{view start   "fire1"}
	}
	{on break_armor
		{if name "blast"
			{if volume "body"
				{call "explosion"}
			}
                		}
	}
	{on bullet_hit
		{if volume "body"
			{if  tagged "isbodypierced"
				{if rand 0.3
					{call "_explosion"}
					{tags remove "isbodypierced"}
				}
			}
		}
	}
	{on "_explosion"
		{call "__explosion"}
		{spawn "fuel_die"}
		{blastwave c4 5 r0 4 r1 15}
		{fire radius 5 time 15 heating 10}
	}
	{on "__explosion"
		{set "big_explosion" 0}
		{if explosive_amount 50         
			{blastwave c4 30 r0 8 r1 16}     
			{blastwave c4 3 r0 20 r1 30}
			{spawn "train_die" "basis"}
			{set "big_explosion" 1}
		}
	}
	{on fire "mgun1"
		{view start   "flame1"}
		{kill_delay "fire1"}
		{delay 0.5 "fire1"
			{view pause   "flame1"}
		}
	}
	{on operatable on	
		{view start	"fire1"}
	}	
	{on operatable off		
		{view stop	"fire1"}
	}
}
{"ot-130 tank"
	("t26_sound")
	("burn_by_engine" args 0.3)	
	{on spawn
		{add_view "flamer_fire" "flame1" "foresight1"}
		{add_view "flamer_fire_barrel" "fire1" "foresight1"}
		{view show	"fire1"}
		{view start	"fire1"}
	}
	{on operatable on	
		{view start	"fire1"}
	}	
	{on operatable off		
		{view stop	"fire1"}
	}
	{on break_armor
		{if name "blast"
			{if volume "body"
				{call "explosion"}
			}
                		}
	}
	{on bullet_hit
		{if volume "body"
			{if  tagged "isbodypierced"
				{if rand 0.3
					{call "_explosion"}
					{tags remove "isbodypierced"}
				}
			}
		}
	}
	{on "_explosion"
		{call "__explosion"}
		{spawn "fuel_die"}
		{blastwave c4 5 r0 4 r1 15}
		{fire radius 5 time 15 heating 10}
	}
	{on "__explosion"
		{set "big_explosion" 0}
		{if explosive_amount 50         
			{blastwave c4 30 r0 8 r1 16}     
			{blastwave c4 3 r0 20 r1 30}
			{spawn "train_die" "basis"}
			{set "big_explosion" 1}
		}
	}
	{on fire "flamer1"
		{view start	"flame1"}
		{kill_delay "fire1"}
		{delay 0.5 "fire1"
			{view pause	"flame1"}
		}
	}
}