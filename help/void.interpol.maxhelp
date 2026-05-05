{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 9,
			"minor" : 0,
			"revision" : 0,
			"architecture" : "x64",
			"modernui" : 1
		},
		"classnamespace" : "box",
		"rect" : [ 50.0, 50.0, 1080.0, 820.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"description" : "Enhanced line with 16 parametric curve types",
		"digest" : "Enhanced line with 16 parametric curve types",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"assistshowspatchername" : 0,
		"boxes" : [
			{
				"box" : { "id":"obj-title", "maxclass":"comment", "numinlets":1, "numoutlets":0,
					"patching_rect":[20.0, 12.0, 850.0, 28.0],
					"text":"void.interpol — 16 parametric curve types",
					"fontsize":18.0 }
			},
			{
				"box" : { "id":"obj-subtitle", "maxclass":"comment", "numinlets":1, "numoutlets":0,
					"patching_rect":[20.0, 38.0, 1000.0, 22.0],
					"text":"Drop-in line replacement. Curves can take parameters: \"value time curve_name [param1 [param2 ...]]\". Defaults if params omitted." }
			},

			{
				"box" : { "id":"obj-s1", "maxclass":"comment", "numinlets":1, "numoutlets":0,
					"patching_rect":[20.0, 75.0, 1040.0, 22.0],
					"text":"1) NO-PARAM CURVES — click each to test:",
					"fontsize":13.0, "fontface":1 }
			},
			{ "box":{ "id":"m-linear", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 100.0, 110.0, 22.0], "text":"linear 0. 0 1. 2000" } },
			{ "box":{ "id":"m-sine",   "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[140.0, 100.0, 110.0, 22.0], "text":"sine 0. 0 1. 2000" } },
			{ "box":{ "id":"m-cosine", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[260.0, 100.0, 110.0, 22.0], "text":"cosine 0. 0 1. 2000" } },
			{ "box":{ "id":"m-square", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[380.0, 100.0, 110.0, 22.0], "text":"square 0. 0 1. 2000" } },
			{ "box":{ "id":"m-sqrt",   "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[500.0, 100.0, 110.0, 22.0], "text":"sqrt 0. 0 1. 2000" } },

			{
				"box" : { "id":"obj-s2", "maxclass":"comment", "numinlets":1, "numoutlets":0,
					"patching_rect":[20.0, 140.0, 1040.0, 22.0],
					"text":"2) PARAMETRIC CURVES — change the param to feel the difference:",
					"fontsize":13.0, "fontface":1 }
			},
			{ "box":{ "id":"m-exp1",   "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 165.0, 130.0, 22.0], "text":"exp 1.5 0. 0 1. 2000" } },
			{ "box":{ "id":"m-exp2",   "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[160.0, 165.0, 130.0, 22.0], "text":"exp 3 0. 0 1. 2000" } },
			{ "box":{ "id":"m-exp3",   "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[300.0, 165.0, 130.0, 22.0], "text":"exp 6 0. 0 1. 2000" } },
			{ "box":{ "id":"m-exp4",   "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[440.0, 165.0, 130.0, 22.0], "text":"exp 10 0. 0 1. 2000" } },
			{ "box":{ "id":"obj-c-exp", "maxclass":"comment", "numinlets":1, "numoutlets":0, "patching_rect":[580.0, 168.0, 200.0, 20.0], "text":"← exp k=1.5, 3, 6, 10 (slope)" } },

			{ "box":{ "id":"m-pow1",   "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 192.0, 130.0, 22.0], "text":"power 0.5 0. 0 1. 2000" } },
			{ "box":{ "id":"m-pow2",   "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[160.0, 192.0, 130.0, 22.0], "text":"power 2 0. 0 1. 2000" } },
			{ "box":{ "id":"m-pow3",   "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[300.0, 192.0, 130.0, 22.0], "text":"power 4 0. 0 1. 2000" } },
			{ "box":{ "id":"m-pow4",   "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[440.0, 192.0, 130.0, 22.0], "text":"power 8 0. 0 1. 2000" } },
			{ "box":{ "id":"obj-c-pow", "maxclass":"comment", "numinlets":1, "numoutlets":0, "patching_rect":[580.0, 195.0, 200.0, 20.0], "text":"← power n=0.5, 2, 4, 8" } },

			{ "box":{ "id":"m-ein1", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 220.0, 150.0, 22.0], "text":"ease_in 2 0. 0 1. 2000" } },
			{ "box":{ "id":"m-ein2", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[180.0, 220.0, 150.0, 22.0], "text":"ease_out 2 0. 0 1. 2000" } },
			{ "box":{ "id":"m-ein3", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[340.0, 220.0, 180.0, 22.0], "text":"ease_in_out 4 0. 0 1. 2000" } },
			{ "box":{ "id":"obj-c-ease", "maxclass":"comment", "numinlets":1, "numoutlets":0, "patching_rect":[530.0, 223.0, 250.0, 20.0], "text":"← ease_in/out/in_out (exp param)" } },

			{
				"box" : { "id":"obj-s3", "maxclass":"comment", "numinlets":1, "numoutlets":0,
					"patching_rect":[20.0, 250.0, 1040.0, 22.0],
					"text":"3) BEZIER — CSS-style cubic + quadratic. Try cubic-bezier.com to design your own:",
					"fontsize":13.0, "fontface":1 }
			},
			{ "box":{ "id":"m-bz1", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 275.0, 220.0, 22.0], "text":"bezier 0.42 0 0.58 1 0. 0 1. 2000" } },
			{ "box":{ "id":"m-bz2", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[250.0, 275.0, 220.0, 22.0], "text":"bezier 0.25 1 0.25 1 0. 0 1. 2000" } },
			{ "box":{ "id":"m-bz3", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[480.0, 275.0, 240.0, 22.0], "text":"bezier 0.68 -0.55 0.27 1.55 0. 0 1. 2000" } },
			{ "box":{ "id":"obj-c-bz", "maxclass":"comment", "numinlets":1, "numoutlets":0, "patching_rect":[730.0, 278.0, 280.0, 20.0], "text":"← ease, ease-out fast, back/overshoot" } },

			{ "box":{ "id":"m-bz2a", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 302.0, 200.0, 22.0], "text":"bezier2 0.5 0 0. 0 1. 2000" } },
			{ "box":{ "id":"m-bz2b", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[230.0, 302.0, 200.0, 22.0], "text":"bezier2 0.5 1 0. 0 1. 2000" } },
			{ "box":{ "id":"obj-c-bz2", "maxclass":"comment", "numinlets":1, "numoutlets":0, "patching_rect":[440.0, 305.0, 240.0, 20.0], "text":"← quadratic bezier (1 control point)" } },

			{
				"box" : { "id":"obj-s4", "maxclass":"comment", "numinlets":1, "numoutlets":0,
					"patching_rect":[20.0, 332.0, 1040.0, 22.0],
					"text":"4) BEND, SIGMOID — continuous curve shapes:",
					"fontsize":13.0, "fontface":1 }
			},
			{ "box":{ "id":"m-bn1", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 357.0, 130.0, 22.0], "text":"bend -0.8 0. 0 1. 2000" } },
			{ "box":{ "id":"m-bn2", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[160.0, 357.0, 130.0, 22.0], "text":"bend -0.4 0. 0 1. 2000" } },
			{ "box":{ "id":"m-bn3", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[300.0, 357.0, 130.0, 22.0], "text":"bend 0.4 0. 0 1. 2000" } },
			{ "box":{ "id":"m-bn4", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[440.0, 357.0, 130.0, 22.0], "text":"bend 0.8 0. 0 1. 2000" } },
			{ "box":{ "id":"obj-c-bn", "maxclass":"comment", "numinlets":1, "numoutlets":0, "patching_rect":[580.0, 360.0, 220.0, 20.0], "text":"← bend in [-1, 1] (curve~ style)" } },

			{ "box":{ "id":"m-sg1", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 384.0, 150.0, 22.0], "text":"sigmoid 3 0. 0 1. 2000" } },
			{ "box":{ "id":"m-sg2", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[180.0, 384.0, 150.0, 22.0], "text":"sigmoid 6 0. 0 1. 2000" } },
			{ "box":{ "id":"m-sg3", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[340.0, 384.0, 150.0, 22.0], "text":"sigmoid 12 0. 0 1. 2000" } },
			{ "box":{ "id":"obj-c-sg", "maxclass":"comment", "numinlets":1, "numoutlets":0, "patching_rect":[500.0, 387.0, 220.0, 20.0], "text":"← sigmoid steepness 3, 6, 12" } },

			{
				"box" : { "id":"obj-s5", "maxclass":"comment", "numinlets":1, "numoutlets":0,
					"patching_rect":[20.0, 414.0, 1040.0, 22.0],
					"text":"5) PHYSICAL CURVES — spring, bounce, elastic (will overshoot/oscillate, watch the multislider!):",
					"fontsize":13.0, "fontface":1 }
			},
			{ "box":{ "id":"m-sp1", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 440.0, 150.0, 22.0], "text":"spring 1 0. 0 1. 2000" } },
			{ "box":{ "id":"m-sp2", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[180.0, 440.0, 150.0, 22.0], "text":"spring 3 0. 0 1. 2000" } },
			{ "box":{ "id":"m-sp3", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[340.0, 440.0, 150.0, 22.0], "text":"spring 5 0. 0 1. 2000" } },
			{ "box":{ "id":"obj-c-sp", "maxclass":"comment", "numinlets":1, "numoutlets":0, "patching_rect":[500.0, 443.0, 250.0, 20.0], "text":"← spring with 1, 3, 5 oscillations" } },

			{ "box":{ "id":"m-bc1", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 467.0, 150.0, 22.0], "text":"bounce 2 0. 0 1. 2000" } },
			{ "box":{ "id":"m-bc2", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[180.0, 467.0, 150.0, 22.0], "text":"bounce 4 0. 0 1. 2000" } },
			{ "box":{ "id":"m-bc3", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[340.0, 467.0, 150.0, 22.0], "text":"bounce 6 0. 0 1. 2000" } },
			{ "box":{ "id":"obj-c-bc", "maxclass":"comment", "numinlets":1, "numoutlets":0, "patching_rect":[500.0, 470.0, 250.0, 20.0], "text":"← bounce 2, 4, 6 bounces" } },

			{ "box":{ "id":"m-el1", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 494.0, 150.0, 22.0], "text":"elastic 1 0. 0 1. 2000" } },
			{ "box":{ "id":"m-el2", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[180.0, 494.0, 150.0, 22.0], "text":"elastic 2 0. 0 1. 2000" } },
			{ "box":{ "id":"m-el3", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[340.0, 494.0, 150.0, 22.0], "text":"elastic 4 0. 0 1. 2000" } },
			{ "box":{ "id":"obj-c-el", "maxclass":"comment", "numinlets":1, "numoutlets":0, "patching_rect":[500.0, 497.0, 250.0, 20.0], "text":"← elastic with 1, 2, 4 oscillations" } },

			{
				"box" : { "id":"obj-s6", "maxclass":"comment", "numinlets":1, "numoutlets":0,
					"patching_rect":[20.0, 522.0, 1040.0, 22.0],
					"text":"6) MULTI-SEGMENT — different curves per segment:",
					"fontsize":13.0, "fontface":1 }
			},
			{ "box":{ "id":"m-multi1", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 547.0, 380.0, 22.0],
				"text":"0. 0 1. 1500 ease_out 3 0. 1500 spring 2 0.5 1000 sine" } },
			{ "box":{ "id":"m-multi2", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[420.0, 547.0, 400.0, 22.0],
				"text":"0. 0 1. 1000 bezier 0.42 0 0.58 1 0. 1000 bounce 4" } },

			{
				"box" : { "id":"obj-s7", "maxclass":"comment", "numinlets":1, "numoutlets":0,
					"patching_rect":[20.0, 580.0, 1040.0, 22.0],
					"text":"7) TRANSPORT:",
					"fontsize":13.0, "fontface":1 }
			},
			{ "box":{ "id":"m-stop", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[20.0, 605.0, 50.0, 22.0], "text":"stop" } },
			{ "box":{ "id":"m-pause", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[80.0, 605.0, 60.0, 22.0], "text":"pause" } },
			{ "box":{ "id":"m-resume", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[150.0, 605.0, 70.0, 22.0], "text":"resume" } },
			{ "box":{ "id":"m-set", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[230.0, 605.0, 80.0, 22.0], "text":"set 0.5" } },
			{ "box":{ "id":"m-grain", "maxclass":"message", "numinlets":2, "numoutlets":1, "outlettype":[""], "patching_rect":[320.0, 605.0, 80.0, 22.0], "text":"grain 5" } },

			{
				"box" : { "id":"obj-s8", "maxclass":"comment", "numinlets":1, "numoutlets":0,
					"patching_rect":[20.0, 645.0, 1040.0, 22.0],
					"text":"8) THE OBJECT and visual output:",
					"fontsize":13.0, "fontface":1 }
			},

			{ "box":{ "id":"obj-trig", "maxclass":"newobj", "numinlets":1, "numoutlets":2, "outlettype":["bang", ""], "patching_rect":[20.0, 670.0, 80.0, 22.0], "text":"t b clear" } },
			{ "box":{ "id":"obj-interpol", "maxclass":"newobj", "numinlets":1, "numoutlets":2, "outlettype":["float","bang"], "patching_rect":[20.0, 700.0, 220.0, 22.0], "text":"void.interpol 0. 20", "fontsize":13.0 } },

			{ "box":{ "id":"obj-num", "maxclass":"flonum", "numinlets":1, "numoutlets":2, "outlettype":["","bang"], "patching_rect":[20.0, 740.0, 100.0, 22.0], "fontsize":13.0, "format":6 } },
			{ "box":{ "id":"obj-bang", "maxclass":"button", "numinlets":1, "numoutlets":1, "outlettype":["bang"], "patching_rect":[140.0, 740.0, 24.0, 24.0], "parameter_enable":0 } },
			{ "box":{ "id":"obj-c-out", "maxclass":"comment", "numinlets":1, "numoutlets":0, "patching_rect":[175.0, 743.0, 230.0, 20.0], "text":"← value     end-of-ramp →" } },

			{ "box":{ "id":"obj-zl", "maxclass":"newobj", "numinlets":2, "numoutlets":2, "outlettype":["",""], "patching_rect":[260.0, 670.0, 100.0, 22.0], "text":"zl.queue 200" } },
			{ "box":{ "id":"obj-mslider", "maxclass":"multislider", "numinlets":1, "numoutlets":2, "outlettype":["",""],
				"patching_rect":[260.0, 700.0, 800.0, 100.0],
				"size":200, "setminmax":[-0.5, 1.5], "setstyle":0, "slidercolor":[0.4, 0.7, 1.0, 1.0],
				"contdata":1, "settype":0, "drawpeaks":0 } }
		],

		"lines" : [
			{"patchline":{"source":["m-linear",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-sine",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-cosine",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-square",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-sqrt",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-exp1",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-exp2",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-exp3",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-exp4",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-pow1",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-pow2",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-pow3",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-pow4",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-ein1",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-ein2",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-ein3",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-bz1",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-bz2",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-bz3",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-bz2a",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-bz2b",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-bn1",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-bn2",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-bn3",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-bn4",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-sg1",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-sg2",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-sg3",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-sp1",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-sp2",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-sp3",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-bc1",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-bc2",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-bc3",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-el1",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-el2",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-el3",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-multi1",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-multi2",0],"destination":["obj-trig",0]}},
			{"patchline":{"source":["m-stop",0],"destination":["obj-interpol",0]}},
			{"patchline":{"source":["m-pause",0],"destination":["obj-interpol",0]}},
			{"patchline":{"source":["m-resume",0],"destination":["obj-interpol",0]}},
			{"patchline":{"source":["m-set",0],"destination":["obj-interpol",0]}},
			{"patchline":{"source":["m-grain",0],"destination":["obj-interpol",0]}},
			{"patchline":{"source":["obj-trig",0],"destination":["obj-interpol",0]}},
			{"patchline":{"source":["obj-trig",1],"destination":["obj-zl",0]}},
			{"patchline":{"source":["obj-interpol",0],"destination":["obj-num",0]}},
			{"patchline":{"source":["obj-interpol",0],"destination":["obj-zl",0]}},
			{"patchline":{"source":["obj-interpol",1],"destination":["obj-bang",0]}},
			{"patchline":{"source":["obj-zl",0],"destination":["obj-mslider",0]}}
		]
	}
}
