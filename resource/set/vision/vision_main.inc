;= HUMAN =====================================

{"human"
    ("uncover" u(7))
    ("h_fov" h(70))
    ("v_fov" v(200))
    ("vision_human")
}
{"mp_soldier"
    ("uncover" u(10))
    ("h_fov" h(150))
    ("v_fov" v(200))
    ("vision_human")
}
{"mp_tier3"
    ("uncover" u(20))
    ("h_fov" h(150))
    ("v_fov" v(300))
    ("vision_human")
}
{"mp_officer"
    ("uncover" u(50))
    ("h_fov" h(180))
    ("v_fov" v(200))
    ("vision_human")
}
{"mp_sniper"
    ("uncover" u(10))
    ("h_fov" h(180))
    ("v_fov" v(200))
    ("vision_human")
}

;= SPECIAL ===================================

{"soldier_focused"
    ("uncover" u(10))
    ("h_fov" h(30))
    ("v_fov" v(50))
    ("vision_human")
}
{"rifle_telescope"
    ("uncover" u(7))
    ("h_fov" h(360))
    ("v_fov" v(120))
    ("glass" args 7)
}
{"field_glass"
    ("uncover" u(5))
    ("h_fov" h(360))
    ("v_fov" v(120))
    ("glass" args 50)
}

{"comm_glass"
    ("uncover" u(5))
    ("h_fov" h(360))
    ("v_fov" v(120))
    ("glass" args 80)
}

{"recon"
    ("uncover" u(10))
    ("h_fov" h(100))
    ("v_fov" v(100))
    {radius 80}
}

{"recon_binocular"
    ("uncover" u(20))
    ("h_fov" h(35))
    ("v_fov" v(35))
     ("glass" args 50)
   {radius 150}
}

;= CANNON ========================================

{"cannon_main"
    ("uncover" u(5))
    ("h_fov" h(60))
    ("v_fov" v(140))
    ("vision_optic")
}
{"cannon_mgun"
    ("uncover" u(5))
    ("h_fov" h(50))
    ("v_fov" v(140))
    ("vision_human")
}
{"cannon_crew"
    ("uncover" u(5))
    ("h_fov" h(360))
    ("v_fov" v(140))
    ("vision_humancrew")
}

;= VEHICLE & MOTO ============================

{"vehicle_main"
    ("uncover" u(5))
    ("h_fov" h(50))
    ("v_fov" v(140))
    ("vision_human")
}
{"vehicle_top_mgun"
    ("h_fov" h(90))
    ("v_fov" v(140))
    ("vision_human")
}
{"vehicle_top_turret"
    ("uncover" u(1))
    ("h_fov" h(360))
    ("v_fov" v(20))
    ("vision_turret")
}
{"moto"
    ("uncover" u(5))
    ("h_fov" h(30))
    ("v_fov" v(140))
    ("vision_human")
}
{"moto_crew"
    ("uncover" u(5))
    ("h_fov" h(90))
    ("v_fov" v(60))
    ("vision_human")
}
{"moto_around"
    ("uncover" u(3))
    ("h_fov" h(360))
    ("v_fov" v(60))
    ("vision_human")
}

;= TANK ======================================

{"mg_hull"
    ("uncover" u(3))
    ("h_fov" h(5))
    ("v_fov" v(90))
    ("vision_gunner")
}
{"tank_main-l"
    ("uncover" u(5))
    ("h_fov" h(30))
    ("v_fov" v(140))
    ("vision_optic")
}
{"tank_main-m"
    ("uncover" u(5))
    ("h_fov" h(25))
    ("v_fov" v(140))
    ("vision_optic")
}
{"tank_main-h"
    ("uncover" u(5))
    ("h_fov" h(25))
    ("v_fov" v(140))
    ("vision_optic")
}
{"tank_driver"
    ("uncover" u(3))
    ("h_fov" h(50))
    ("v_fov" v(20))
    ("vision_gunner")
}
{"tank_back"
    ("uncover" u(3))
    ("h_fov" h(50))
    ("v_fov" v(120))
    ("vision_gunner")
}
{"none"
}
{"tank_around-l"

}

{"tank_around-m"

}

{"tank_around-h"

}

;= OTHER ======================================

{"cover-detector"
	{uncover 5}
	{h_fov 60}
	{v_fov 120}
	("vision_optic" args 50)
}
{"animal"
	{uncover 2}
	{h_fov 360}
	{v_fov 120}
}
{"searchlight"
	{h_fov 30}
	{v_fov 90}
	("vision_optic" args 60)
}
{"watchtower"
	{h_fov 90}
	{v_fov 90}
    ("vision_optic" args 50)
}
{"marine_main"
	{h_fov 50}
	{v_fov 120}
    ("vision_optic" args 24)
}