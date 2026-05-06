{
    "patcher": {
        "fileversion": 1,
        "appversion": {
            "major": 9,
            "minor": 1,
            "revision": 2,
            "architecture": "x64",
            "modernui": 1
        },
        "classnamespace": "box",
        "rect": [ 130.0, 164.0, 698.0, 404.0 ],
        "boxes": [
            {
                "box": {
                    "id": "obj-11",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 377.0, 275.0, 80.0, 20.0 ],
                    "text": "no more :-)"
                }
            },
            {
                "box": {
                    "id": "obj-8",
                    "maxclass": "button",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "bang" ],
                    "parameter_enable": 0,
                    "patching_rect": [ 114.0, 187.0, 24.0, 24.0 ]
                }
            },
            {
                "box": {
                    "dontreplace": 1,
                    "id": "obj-6",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "patching_rect": [ 118.0, 307.0, 135.0, 22.0 ],
                    "text": "Julien4.local"
                }
            },
            {
                "box": {
                    "id": "obj-24",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 401.0, 173.0, 176.0, 20.0 ],
                    "text": "Developed by Julien Bayle",
                    "textjustification": 2
                }
            },
            {
                "box": {
                    "hidden": 1,
                    "id": "obj-21",
                    "linecount": 5,
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "patching_rect": [ 588.0, 103.0, 107.0, 76.0 ],
                    "text": ";\rmax launchbrowser https://structure-void.com"
                }
            },
            {
                "box": {
                    "handoff": "",
                    "id": "obj-18",
                    "maxclass": "ubutton",
                    "numinlets": 1,
                    "numoutlets": 4,
                    "outlettype": [ "bang", "bang", "", "int" ],
                    "parameter_enable": 0,
                    "patching_rect": [ 588.0, 11.0, 100.0, 100.0 ]
                }
            },
            {
                "box": {
                    "autofit": 1,
                    "forceaspect": 1,
                    "id": "obj-9",
                    "maxclass": "fpic",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "jit_matrix" ],
                    "patching_rect": [ 588.0, 11.0, 100.0, 100.0 ],
                    "pic": "/Users/julien/StructureVoid Dropbox/SV_ADMIN/_COM_PUB_PR/_LOGOS/StructureVoid_.jpg"
                }
            },
            {
                "box": {
                    "id": "obj-13",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 114.0, 335.0, 157.0, 20.0 ],
                    "text": "Get the system hostname"
                }
            },
            {
                "box": {
                    "id": "obj-10",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 171.0, 189.0, 57.0, 20.0 ],
                    "text": "bang it !"
                }
            },
            {
                "box": {
                    "id": "obj-4",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "patching_rect": [ 114.0, 237.0, 107.0, 22.0 ],
                    "text": "void.net.hostname"
                }
            },
            {
                "box": {
                    "border": 0,
                    "filename": "helpdetails.js",
                    "id": "obj-1",
                    "ignoreclick": 1,
                    "jsarguments": [ "void.net.hostname" ],
                    "maxclass": "jsui",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "parameter_enable": 0,
                    "patching_rect": [ 10.0, 11.0, 567.0, 160.0 ]
                }
            },
            {
                "box": {
                    "background": 1,
                    "bgcolor": [ 0.101961, 0.101961, 0.101961, 1.0 ],
                    "fontname": "Arial Bold",
                    "hint": "",
                    "id": "obj-93",
                    "ignoreclick": 1,
                    "legacytextcolor": 1,
                    "maxclass": "textbutton",
                    "numinlets": 1,
                    "numoutlets": 3,
                    "outlettype": [ "", "", "int" ],
                    "parameter_enable": 0,
                    "patching_rect": [ 145.0, 189.0, 20.0, 20.0 ],
                    "rounded": 60.0,
                    "saved_attribute_attributes": {
                        "bgcolor": {
                            "expression": "themecolor.lesson_step_bottomgradient"
                        }
                    },
                    "text": "1",
                    "textcolor": [ 1.0, 1.0, 1.0, 1.0 ]
                }
            }
        ],
        "lines": [
            {
                "patchline": {
                    "destination": [ "obj-21", 0 ],
                    "source": [ "obj-18", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-6", 1 ],
                    "midpoints": [ 123.5, 294.0, 243.5, 294.0 ],
                    "source": [ "obj-4", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-4", 0 ],
                    "source": [ "obj-8", 0 ]
                }
            }
        ],
        "autosave": 0
    }
}