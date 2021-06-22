BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "procedures" (
	"procedureName"	VARCHAR(255),
	PRIMARY KEY("procedureName")
);
CREATE TABLE IF NOT EXISTS "variables" (
	"variableName"	VARCHAR(255),
	"stmtNum"	VARCHAR(255),
	"procedureName"	VARCHAR(255)
);
CREATE TABLE IF NOT EXISTS "reads" (
	"stmtNum"	VARCHAR(255),
	"procedureName"	VARCHAR(255)
);
CREATE TABLE IF NOT EXISTS "statements" (
	"stmtNum"	VARCHAR(255),
	"stmtType"	VARCHAR(255),
	"procedureName"	VARCHAR(255),
	PRIMARY KEY("stmtNum")
);
CREATE TABLE IF NOT EXISTS "constants" (
	"constantName"	VARCHAR(255),
	"stmtNum"	VARCHAR(255),
	"procedureName"	VARCHAR(255)
);
CREATE TABLE IF NOT EXISTS "prints" (
	"stmtNum"	VARCHAR(255),
	"procedureName"	VARCHAR(255)
);
CREATE TABLE IF NOT EXISTS "assigns" (
	"stmtNum"	VARCHAR(255),
	"procedureName"	VARCHAR(255),
	PRIMARY KEY("stmtNum")
);
CREATE TABLE IF NOT EXISTS "ifs" (
	"stmtNum"	VARCHAR(255),
	"procedureName"	VARCHAR(255),
	"startstmt"	VARCHAR(255),
	"endstmt"	VARCHAR(255),
	PRIMARY KEY("stmtNum")
);
CREATE TABLE IF NOT EXISTS "whiles" (
	"stmtNum"	VARCHAR(255),
	"procedureName"	VARCHAR(255),
	"startstmt"	VARCHAR(255),
	"endstmt"	VARCHAR(255),
	PRIMARY KEY("stmtNum")
);
CREATE TABLE IF NOT EXISTS "parents" (
	"parent"	VARCHAR(255),
	"procedureName"	VARCHAR(255),
	"child"	VARCHAR(255)
);
CREATE TABLE IF NOT EXISTS "parentstar" (
	"ancestor"	VARCHAR(255),
	"procedureName"	VARCHAR(255),
	"child"	VARCHAR(255)
);
CREATE TABLE IF NOT EXISTS "follows" (
	"procedureName"	VARCHAR(255),
	"stmt"	VARCHAR(255),
	"scope"	VARCHAR(255),
	"level"	VARCHAR(255)
);
CREATE TABLE IF NOT EXISTS "modifies" (
	"stmtNum"	VARCHAR(255),
	"procedureName"	VARCHAR(255),
	"variable"	VARCHAR(255)
);
CREATE TABLE IF NOT EXISTS "uses" (
	"stmtNum"	VARCHAR(255),
	"procedureName"	VARCHAR(255),
	"variable"	VARCHAR(255)
);
CREATE TABLE IF NOT EXISTS "expression" (
	"stmtNum"	VARCHAR(255),
	"procedureName"	VARCHAR(255),
	"assign"	VARCHAR(255),
	"postfix"	VARCHAR(255),
	PRIMARY KEY("stmtNum")
);
CREATE TABLE IF NOT EXISTS "pattern" (
	"stmtNum"	VARCHAR(255),
	"fullExp"	VARCHAR(255),
	"partExp"	VARCHAR(255),
	"procedureName"	VARCHAR(255)
);
INSERT INTO "procedures" ("procedureName") VALUES ('computeCentroid');
INSERT INTO "variables" ("variableName","stmtNum","procedureName") VALUES ('x','1','computeCentroid'),
 ('x','1','computeCentroid'),
 ('z','2','computeCentroid'),
 ('gg','3','computeCentroid'),
 ('ll','4','computeCentroid'),
 ('bb','5','computeCentroid'),
 ('aa','6','computeCentroid'),
 ('test1','7','computeCentroid'),
 ('x','8','computeCentroid'),
 ('x','8','computeCentroid'),
 ('y','8','computeCentroid'),
 ('y','8','computeCentroid'),
 ('digit','9','computeCentroid'),
 ('number','9','computeCentroid'),
 ('sum','10','computeCentroid'),
 ('sum','10','computeCentroid'),
 ('digit','10','computeCentroid'),
 ('number','11','computeCentroid'),
 ('number','11','computeCentroid'),
 ('count','12','computeCentroid'),
 ('flag','13','computeCentroid'),
 ('long','14','computeCentroid'),
 ('test','15','computeCentroid'),
 ('tt','16','computeCentroid'),
 ('xx','17','computeCentroid'),
 ('flag','18','computeCentroid'),
 ('iflong','19','computeCentroid'),
 ('test2','20','computeCentroid'),
 ('z','21','computeCentroid'),
 ('gg','22','computeCentroid'),
 ('er','23','computeCentroid'),
 ('pp','24','computeCentroid'),
 ('xx','24','computeCentroid'),
 ('qq','24','computeCentroid'),
 ('qq','24','computeCentroid'),
 ('temp','25','computeCentroid'),
 ('yes','26','computeCentroid'),
 ('bb','27','computeCentroid'),
 ('xo','28','computeCentroid'),
 ('y','29','computeCentroid'),
 ('x','30','computeCentroid');
INSERT INTO "reads" ("stmtNum","procedureName") VALUES ('7','computeCentroid'),
 ('20','computeCentroid'),
 ('25','computeCentroid'),
 ('28','computeCentroid');
INSERT INTO "statements" ("stmtNum","stmtType","procedureName") VALUES ('1','assign','computeCentroid'),
 ('2','if','computeCentroid'),
 ('3','assign','computeCentroid'),
 ('4','assign','computeCentroid'),
 ('5','assign','computeCentroid'),
 ('6','assign','computeCentroid'),
 ('7','read','computeCentroid'),
 ('8','while','computeCentroid'),
 ('9','assign','computeCentroid'),
 ('10','assign','computeCentroid'),
 ('11','assign','computeCentroid'),
 ('12','if','computeCentroid'),
 ('13','assign','computeCentroid'),
 ('14','print','computeCentroid'),
 ('15','while','computeCentroid'),
 ('16','assign','computeCentroid'),
 ('17','assign','computeCentroid'),
 ('18','assign','computeCentroid'),
 ('19','print','computeCentroid'),
 ('20','read','computeCentroid'),
 ('21','if','computeCentroid'),
 ('22','assign','computeCentroid'),
 ('23','assign','computeCentroid'),
 ('24','while','computeCentroid'),
 ('25','read','computeCentroid'),
 ('26','print','computeCentroid'),
 ('27','assign','computeCentroid'),
 ('28','read','computeCentroid'),
 ('29','assign','computeCentroid'),
 ('30','assign','computeCentroid');
INSERT INTO "constants" ("constantName","stmtNum","procedureName") VALUES ('1','1','computeCentroid'),
 ('10','2','computeCentroid'),
 ('66','3','computeCentroid'),
 ('88','4','computeCentroid'),
 ('77','5','computeCentroid'),
 ('78','6','computeCentroid'),
 ('3','8','computeCentroid'),
 ('3','8','computeCentroid'),
 ('2','9','computeCentroid'),
 ('3','11','computeCentroid'),
 ('5','12','computeCentroid'),
 ('6','13','computeCentroid'),
 ('123','16','computeCentroid'),
 ('321','17','computeCentroid'),
 ('7','18','computeCentroid'),
 ('10','21','computeCentroid'),
 ('666','22','computeCentroid'),
 ('8901212345678901234567890123456789012345678901234567890','23','computeCentroid'),
 ('77','27','computeCentroid'),
 ('4','29','computeCentroid'),
 ('8','30','computeCentroid');
INSERT INTO "prints" ("stmtNum","procedureName") VALUES ('14','computeCentroid'),
 ('19','computeCentroid'),
 ('26','computeCentroid');
INSERT INTO "assigns" ("stmtNum","procedureName") VALUES ('1','computeCentroid'),
 ('3','computeCentroid'),
 ('4','computeCentroid'),
 ('5','computeCentroid'),
 ('6','computeCentroid'),
 ('9','computeCentroid'),
 ('10','computeCentroid'),
 ('11','computeCentroid'),
 ('13','computeCentroid'),
 ('16','computeCentroid'),
 ('17','computeCentroid'),
 ('18','computeCentroid'),
 ('22','computeCentroid'),
 ('23','computeCentroid'),
 ('27','computeCentroid'),
 ('29','computeCentroid'),
 ('30','computeCentroid');
INSERT INTO "parents" ("parent","procedureName","child") VALUES ('0','computeCentroid','1'),
 ('2','computeCentroid','3'),
 ('2','computeCentroid','4'),
 ('2','computeCentroid','5'),
 ('2','computeCentroid','6'),
 ('0','computeCentroid','7'),
 ('8','computeCentroid','9'),
 ('8','computeCentroid','10'),
 ('8','computeCentroid','11'),
 ('12','computeCentroid','13'),
 ('12','computeCentroid','14'),
 ('15','computeCentroid','16'),
 ('15','computeCentroid','17'),
 ('12','computeCentroid','18'),
 ('12','computeCentroid','19'),
 ('0','computeCentroid','20'),
 ('21','computeCentroid','22'),
 ('21','computeCentroid','23'),
 ('24','computeCentroid','25'),
 ('24','computeCentroid','26'),
 ('21','computeCentroid','27'),
 ('21','computeCentroid','28'),
 ('0','computeCentroid','29'),
 ('0','computeCentroid','30');
INSERT INTO "parentstar" ("ancestor","procedureName","child") VALUES ('2','computeCentroid','3'),
 ('2','computeCentroid','4'),
 ('2','computeCentroid','5'),
 ('2','computeCentroid','6'),
 ('8','computeCentroid','9'),
 ('8','computeCentroid','10'),
 ('8','computeCentroid','11'),
 ('8','computeCentroid','13'),
 ('8','computeCentroid','14'),
 ('8','computeCentroid','16'),
 ('8','computeCentroid','17'),
 ('8','computeCentroid','18'),
 ('8','computeCentroid','19'),
 ('21','computeCentroid','22'),
 ('21','computeCentroid','23'),
 ('21','computeCentroid','25'),
 ('21','computeCentroid','26'),
 ('21','computeCentroid','27'),
 ('21','computeCentroid','28');
INSERT INTO "modifies" ("stmtNum","procedureName","variable") VALUES ('1','computeCentroid','x'),
 ('3','computeCentroid','gg'),
 ('4','computeCentroid','ll'),
 ('5','computeCentroid','bb'),
 ('6','computeCentroid','aa'),
 ('7','computeCentroid','test1'),
 ('9','computeCentroid','digit'),
 ('10','computeCentroid','sum'),
 ('11','computeCentroid','number'),
 ('13','computeCentroid','flag'),
 ('16','computeCentroid','tt'),
 ('17','computeCentroid','xx'),
 ('18','computeCentroid','flag'),
 ('20','computeCentroid','test2'),
 ('22','computeCentroid','gg'),
 ('23','computeCentroid','er'),
 ('25','computeCentroid','temp'),
 ('27','computeCentroid','bb'),
 ('28','computeCentroid','xo'),
 ('29','computeCentroid','y'),
 ('30','computeCentroid','x');
INSERT INTO "uses" ("stmtNum","procedureName","variable") VALUES ('1','computeCentroid','x'),
 ('2','computeCentroid','z'),
 ('8','computeCentroid','x'),
 ('8','computeCentroid','x'),
 ('8','computeCentroid','y'),
 ('8','computeCentroid','y'),
 ('9','computeCentroid','number'),
 ('10','computeCentroid','sum'),
 ('10','computeCentroid','digit'),
 ('11','computeCentroid','number'),
 ('12','computeCentroid','count'),
 ('14','computeCentroid','long'),
 ('15','computeCentroid','test'),
 ('19','computeCentroid','iflong'),
 ('21','computeCentroid','z'),
 ('24','computeCentroid','pp'),
 ('24','computeCentroid','xx'),
 ('24','computeCentroid','qq'),
 ('26','computeCentroid','yes');
INSERT INTO "expression" ("stmtNum","procedureName","assign","postfix") VALUES ('1','computeCentroid','x','x1+'),
 ('2','computeCentroid','conditionLoop','z'),
 ('3','computeCentroid','gg','66'),
 ('4','computeCentroid','ll','88'),
 ('5','computeCentroid','bb','77'),
 ('6','computeCentroid','aa','78'),
 ('8','computeCentroid','conditionLoop','xx*yy*+'),
 ('9','computeCentroid','digit','number2%'),
 ('10','computeCentroid','sum','sumdigit+'),
 ('11','computeCentroid','number','number3/'),
 ('12','computeCentroid','conditionLoop','count'),
 ('13','computeCentroid','flag','6'),
 ('16','computeCentroid','tt','123'),
 ('17','computeCentroid','xx','321'),
 ('18','computeCentroid','flag','7'),
 ('21','computeCentroid','conditionLoop','z'),
 ('22','computeCentroid','gg','666'),
 ('23','computeCentroid','er','8901212345678901234567890123456789012345678901234567890'),
 ('24','computeCentroid','conditionLoop','ppxx+'),
 ('27','computeCentroid','bb','77'),
 ('29','computeCentroid','y','4'),
 ('30','computeCentroid','x','8');
COMMIT;
