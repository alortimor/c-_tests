-- Reference Data
WHENEVER SQLERROR EXIT SQL.SQLCODE
set echo on

insert into warehouse
(w_id,W_name,W_STREET_1 ,W_STREET_2  ,W_CITY ,w_state,W_ZIP,W_TAX ,W_YTD )
values (1,'WHZ 1','Long Street',null,'Sacramento','CA','714',0.22,82476.22);
insert into warehouse
(w_id,W_name,W_STREET_1 ,W_STREET_2  ,W_CITY ,w_state,W_ZIP,W_TAX ,W_YTD )
values (2,'WHZ 2','Onslow Square','Short Street','Jefferson City','MD','443',0.3,82336.22);
insert into warehouse
(w_id,W_name,W_STREET_1 ,W_STREET_2  ,W_CITY ,w_state,W_ZIP,W_TAX ,W_YTD )
values (3,'WHZ 3','Dale Avenue','Shooters Hill','Lansing','MI','947',0.2,54645.11);
insert into warehouse
(w_id,W_name,W_STREET_1 ,W_STREET_2  ,W_CITY ,w_state,W_ZIP,W_TAX ,W_YTD )
values (4,'WHZ 4','Liverpool Way',null,'Boston','MA','882',0.4,394657.11);
insert into warehouse
(w_id,W_name,W_STREET_1 ,W_STREET_2  ,W_CITY ,w_state,W_ZIP,W_TAX ,W_YTD )
values (5,'WHZ 5','Flamingo Drive','Unit 2','Albany','NJ','716',0.25,297898.22);
insert into warehouse
(w_id,W_name,W_STREET_1 ,W_STREET_2  ,W_CITY ,w_state,W_ZIP,W_TAX ,W_YTD )
values (6,'WHZ 6','Portland Avenue','South Side','Springfield','IL','872',0.15,64536.22);
insert into warehouse
(w_id,W_name,W_STREET_1 ,W_STREET_2  ,W_CITY ,w_state,W_ZIP,W_TAX ,W_YTD )
values (7,'WHZ 7','Dean Street','Site 67','Tallahassee','FL','954',0.1,6357211.22);
insert into warehouse
(w_id,W_name,W_STREET_1 ,W_STREET_2  ,W_CITY ,w_state,W_ZIP,W_TAX ,W_YTD )
values (8,'WHZ 8','Jefferson Way','Upper Street','Baton Rouge','LA','33551',0.2, 916753.22);
insert into warehouse
(w_id,W_name,W_STREET_1 ,W_STREET_2  ,W_CITY ,w_state,W_ZIP,W_TAX ,W_YTD )
values (9,'WHZ 9','Thomas Road',null,'Raleigh','NC','6997',0.21, 232547.22);
insert into warehouse
(w_id,W_name,W_STREET_1 ,W_STREET_2  ,W_CITY ,w_state,W_ZIP,W_TAX ,W_YTD )
values (10,'WHZ 10','Joel Street',null,'Topeka','KS','4325',0.2, 546812.22);
insert into warehouse
(w_id,W_name,W_STREET_1 ,W_STREET_2  ,W_CITY ,w_state,W_ZIP,W_TAX ,W_YTD )
values (11,'WHZ 11','Wilcow Way','Jain Street','Harrisburg','PA','717',0.35, 84756.11);
insert into warehouse
(w_id,W_name,W_STREET_1 ,W_STREET_2  ,W_CITY ,w_state,W_ZIP,W_TAX ,W_YTD )
values (12,'WHZ 12','Churchill Street',null,'Phoenix','AZ','205',0.28, 665512.00);

commit;

insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (1,1,'DIST 1','7 W Jackson Blvd','San Jose','Santa Clara','CA',95111,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (2,1,'DIST 2','25 E 75th St #69','Los Angeles','Los Angeles','CA',90034,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (3,1,'DIST 3','6 Greenleaf Ave','San Jose','Santa Clara','CA',95111,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (4,1,'DIST 4','17 Morena Blvd','Camarillo','Ventura','CA',93012,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (5,1,'DIST 5','5 Tomahawk Dr','Los Angeles','Los Angeles','CA',90006,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (6,1,'DIST 6','4 Otis St','Van Nuys','Los Angeles','CA',91405,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (7,1,'DIST 7','701 S Harrison Rd','San Francisco','San Francisco','CA',94104,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (8,1,'DIST 8','30 W 80th St #1995','San Carlos','San Mateo','CA',94070,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (9,1,'DIST 9','20932 Hedley St','Concord','Contra Costa','CA',94520,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (10,1,'DIST 10','69 Marquette Ave','Hayward','Alameda','CA',94545,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (11,2,'DIST 11','28 Runamuck Pl #280','Baltimore','Baltimore City','MD',21224,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (12,2,'DIST 12','2 Cedar Ave #84','Easton','Talbot','MD',21601,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (13,2,'DIST 13','2853 S Central Expy','Glen Burnie','Anne Arundel','MD',21061,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (14,2,'DIST 14','6 Kains Ave','Baltimore','Baltimore City','MD',21215,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (15,2,'DIST 15','5589 Jacksonville Rd','Owings Mills','Baltimore','MD',21117,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (16,2,'DIST 16','6048 Old US Way 51','Preston','Caroline','MD',21655,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (17,2,'DIST 17','28 Warren Rd','Hampstead','Carroll','MD',21074,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (18,2,'DIST 18','96950 Hidden Ln','Aberdeen','Harford','MD',21001,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (19,2,'DIST 19','9648 S Main','Salisbury','Wicomico','MD',21801,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (20,2,'DIST 20','478 Coney Island Ave','Clinton','Prince Georges','MD',20735,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (21,3,'DIST 21','4B Blue Ridge Blvd','Brighton','Livingston','MI',48116,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (22,3,'DIST 22','1 State Route 27','Taylor','Wayne','MI',48180,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (23,3,'DIST 23','7116 Western Ave','Dearborn','Wayne','MI',48126,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (24,3,'DIST 24','560 Civic Center Dr','Ann Arbor','Washtenaw','MI',48103,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (25,3,'DIST 25','57 Haven Ave #90','Southfield','Oakland','MI',48075,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (26,3,'DIST 26','897 Connecticut Ave','Niles','Berrien','MI',49120,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (27,3,'DIST 27','206 Main St #2804','Lansing','Ingham','MI',48933,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (28,3,'DIST 28','40 9th Ave Sw #91','Waterford','Oakland','MI',48329,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (29,3,'DIST 29','958 E Arapahoe Rd','Rochester','Oakland','MI',48307,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (30,3,'DIST 30','89 20th St E779','Sterling Heights','Macomb','MI',48310,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (31,4,'DIST 31','38938 Park Blvd','Boston','Suffolk','MA',2128,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (32,4,'DIST 32','3 Aspen St','Worcester','Worcester','MA',1602,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (33,4,'DIST 33','8 County Center Dr64','Boston','Suffolk','MA',2210,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (34,4,'DIST 34','481 W Lemon St','Middleboro','Plymouth','MA',2346,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (35,4,'DIST 35','523 Marquette Ave','Concord','Middlesex','MA',1742,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (36,4,'DIST 36','1 Midway Rd','Westborough','Worcester','MA',1581,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (37,4,'DIST 37','5 Little River Tpke','Wilmington','Middlesex','MA',1887,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (38,4,'DIST 38','5725 Brickell Ave372','Worcester','Worcester','MA',1602,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (39,4,'DIST 39','4 Carroll St','North Attleboro','Bristol','MA',2760,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (40,4,'DIST 40','8139 I Hwy 10 92','New Bedford','Bristol','MA',2745,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (41,5,'DIST 41','8W Cerritos Ave 54','Bridgeport','Gloucester','NJ',8014,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (42,5,'DIST 42','3273 State St','Middlesex','Middlesex','NJ',8846,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (43,5,'DIST 43','45 E Liberty St','Ridgefield Park','Bergen','NJ',7660,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (44,5,'DIST 44','4 Ralph Ct','Dunellen','Middlesex','NJ',8812,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (45,5,'DIST 45','76 Brooks St #9','Flemington','Hunterdon','NJ',8822,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (46,5,'DIST 46','5307 Sw 152nd Ter615','Monroe Township','Middlesex','NJ',8831,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (47,5,'DIST 47','47565 W Grand Ave','Newark','Essex','NJ',7105,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (48,5,'DIST 48','6794 Lake Dr E','Newark','Essex','NJ',7104,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (49,5,'DIST 49','2726 Charcot Ave','Paterson','Passaic','NJ',7501,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (50,5,'DIST 50','4646 Kaahumanu St','Hackensack','Bergen','NJ',7601,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (51,6,'DIST 51','7 Eads St','Chicago','Cook','IL',60632,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (52,6,'DIST 52','394 Manchester Blvd','Rockford','Winnebago','IL',61109,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (53,6,'DIST 53','4284 Dorigo Ln','Chicago','Cook','IL',60647,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (54,6,'DIST 54','37 Alabama Ave','Evanston','Cook','IL',60201,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (55,6,'DIST 55','4 Warehouse Pt Rd7','Chicago','Cook','IL',60638,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (56,6,'DIST 56','137 Pioneer Way','Chicago','Cook','IL',60604,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (57,6,'DIST 57','44 58th St','Wheeling','Cook','IL',60090,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (58,6,'DIST 58','9 Murfreesboro Rd','Chicago','Cook','IL',60623,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (59,6,'DIST 59','18 Waterloo Rd','Highland Park','Lake','IL',60035,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (60,6,'DIST 60','7 West Ave #1','Palatine','Cook','IL',60067,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (61,7,'DIST 61','678 3rd Ave','Miami','Miami-Dade','FL',33196,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (62,7,'DIST 62','11279 Loytan St','Jacksonville','Duval','FL',32254,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (63,7,'DIST 63','32860 Sierra Rd','Miami','Miami-Dade','FL',33133,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (64,7,'DIST 64','5161 Dorsett Rd','Homestead','Miami-Dade','FL',33030,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (65,7,'DIST 65','8597 W National Av','Cocoa','Brevard','FL',32922,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (66,7,'DIST 66','9 Wales Rd NE914','Homosassa','Citrus','FL',34448,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (67,7,'DIST 67','97 Airport Loop Dr','Jacksonville','Duval','FL',32216,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (68,7,'DIST 68','703 Beville Rd','Opa Locka','Miami-Dade','FL',33054,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (69,7,'DIST 69','189 Village Park Rd','Crestview','Okaloosa','FL',32536,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (70,7,'DIST 70','93 Redmond Rd #492','Orlando','Orange','FL',32803,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (71,8,'DIST 71','9 Tower Ave','Burlington','Boone','LA',70003,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (72,8,'DIST 72','6649 N Blue Gum St','New Orleans','Orleans','LA',70116,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (73,8,'DIST 73','426 Wolf St','Metairie','Jefferson','LA',70002,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (74,8,'DIST 74','3 Secor Rd','New Orleans','Orleans','LA',70112,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (75,8,'DIST 75','6651 Municipal Rd','Houma','Terrebonne','LA',70360,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (76,8,'DIST 76','55 Hawthorne Blvd','Lafayette','Lafayette','LA',70506,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (77,8,'DIST 77','3718 S Main St','New Orleans','Orleans','LA',70130,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (78,8,'DIST 78','43 Huey P Long Ave','Lafayette','Lafayette','LA',70508,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (79,8,'DIST 79','49 N Mays St','Broussard','Lafayette','LA',70518,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (80,8,'DIST 80','393 Hammond Dr','Lafayette','Lafayette','LA',70506,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (81,9,'DIST 81','1088 Pinehurst St','Chapel Hill','Orange','NC',27514,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (82,9,'DIST 82','4 10th St W','High Point','Guilford','NC',27263,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (83,9,'DIST 83','749 W 18th St #45','Smithfield','Johnston','NC',27577,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (84,9,'DIST 84','33 Lewis Rd #46','Burlington','Alamance','NC',27215,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (85,9,'DIST 85','9 Plainsboro Rd 59','Greensboro','Guilford','NC',27409,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (86,9,'DIST 86','987 Main St','Raleigh','Wake','NC',27601,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (87,9,'DIST 87','1482 College Ave','Fayetteville','Cumberland','NC',28301,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (88,9,'DIST 88','88827 Frankford Ave','Greensboro','Guilford','NC',27401,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (89,9,'DIST 89','87 Imperial Ct #79','Fargo','Cass','NC',27633,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (90,9,'DIST 90','2157 Apple Creek Rd','Omaha','Douglas','NC',27682,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (91,10,'DIST 91','86 Nw 66th St #8673','Shawnee','Johnson','KS',66218,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (92,10,'DIST 92','6980 Dorsett Rd','Abilene','Dickinson','KS',67410,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (93,10,'DIST 93','7219 Woodfield Rd','Overland Park','Johnson','KS',66204,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (94,10,'DIST 94','810 Jacksonville Rd7','Hays','Ellis','KS',67601,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (95,10,'DIST 95','8284 Hart St','Abilene','Dickinson','KS',67410,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (96,10,'DIST 96','9 Tower Ave','Burlington','Boone','KS',67520,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (97,10,'DIST 97','9390 S Howell Ave','Albany','Dougherty','KS',66352,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (98,10,'DIST 98','5384 Southwyck Blvd','Douglasville','Douglas','KS',65268,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (99,10,'DIST 99','45 2nd Ave #9759','Hays','Fulton','KS',67840,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (100,11,'DIST 100','26 Montgomery St','Shawnee','Fulton','KS',67333,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (101,11,'DIST 101','6 S 33rd St','Aston','Delaware','PA',19014,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (102,11,'DIST 102','209 Decker Dr','Philadelphia','Philadelphia','PA',19132,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (103,11,'DIST 103','71 San Mateo Ave','Wayne','Delaware','PA',19087,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (104,11,'DIST 104','1428 Foster Av 4121','Jenkintown','Montgomery','PA',19046,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (105,11,'DIST 105','143 Pennsylvania Ave','Huntingdon Valley','Montgomery','PA',19006,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (106,11,'DIST 106','7 W 32nd St','Erie','Erie','PA',16502,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (107,11,'DIST 107','3 Fort Worth Ave','Philadelphia','Philadelphia','PA',19106,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (108,11,'DIST 108','555 Main St','Erie','Erie','PA',16502,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (109,11,'DIST 109','83 County Rd 437 858','Clarks Summit','Lackawanna','PA',18411,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (110,12,'DIST 110','63381 Jenks Ave','Philadelphia','Philadelphia','PA',19134,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (111,12,'DIST 111','1844 Southern Blvd','Phoenix','Maricopa','AZ',85034,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (112,12,'DIST 112','73 State Road 434 E','Phoenix','Maricopa','AZ',85013,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (113,12,'DIST 113','1 Huntwood Ave','Phoenix','Maricopa','AZ',85017,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (114,12,'DIST 114','4 58th St #3519','Scottsdale','Maricopa','AZ',85254,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (115,12,'DIST 115','96541 W Central Blvd','Phoenix','Maricopa','AZ',85034,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (116,12,'DIST 116','347 Chestnut St','Peoria','Maricopa','AZ',85381,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (117,12,'DIST 117','10759 Main St','Scottsdale','Maricopa','AZ',85260,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (118,12,'DIST 118','86350 Roszel Rd','Phoenix','Maricopa','AZ',85012,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (119,12,'DIST 119','9 W Central Ave','Phoenix','Maricopa','AZ',85013,0,1);
insert into district (D_ID,D_W_ID,D_NAME,D_STREET_1,D_STREET_2,D_CITY,D_STATE,D_ZIP,D_YTD,D_NEXT_O_ID) values (120,12,'DIST 120','72 Southern Blvd','Mesa','Maricopa','AZ',85204,0,1);

update district d set d.d_tax = (select w.w_tax from warehouse w
where d.d_w_id = w.w_id);

commit;

set echo off
