Autori: xmurga01, xhorac19
- Autori jednotlivých súborov sú uvedení v hlavičkových súboroch.

Tento súbor slúži na orientačný prehľad kompletnosti implementácie projektu.
Časti implementácie sú rozdelené do troch sekcií:
-plne implementované
-čiastočne implementované
-neimplementované

------- Kompletne implementované -------
-Načítanie, ukladanie a editácia diagramov
-Prvky sekvenčného diagramu odpovedajú diagramu tried
-Pri interaktívnych zásahoch je zohľadnená previazanosť diagramov
-Aplikácia zvýrazňuje nekonzistencie po interaktívnych zásahoch
-Diagram tried		-aplikácia načíta textové parametry diagramu tried a zobrazí ho so všetkými komponentami
			-podpora všetkých 4 možných modifikátorov
			-triedy môžu byť prepojené pomocou vzťahov
-Sekvenčný diagram	-aplikácia načíta textové parametry sekvenčného diagramu a zobrazí ho so všetkými komponentami
			-aplikácia podporuje tvorbu/zánik a aktiváciu/deaktiváciu objektov

------- Čiastočne implementované -------
-Aplikácia umožňuje pracovat len s 1 sekvenčným diagramom
-Ak sa pri načítaní zo súboru nájdu nekonzistencie, užívatel dostane chybové hlásenie o inkonzistencii v súbore a program súbor nenačíta
-Pri zásahu do súboru môže program spadnúť
-Sekvenčný diagram	-objekty môžu spolu interagovať pomocou synchrónnych správ a returnov, asynchrónne správy a správy na tvorbu/zánik objektov nie sú implementované

------- Neimplementované ---------------
-Aplikácia nepodporuje rozhrania v diagrame tried
-Aplikácia nepodporuje operáciu undo
-Generalizácia je implementovaná iba vizuálne v diagrame tried
-Aplikácia nepodporuje preťažovanie metód

------- Prevzatý modifikovaný kód -------
void RelationGraphicsObject::LineLineCollision(QPointF*, QLineF, QLineF) ---- http://jeffreythompson.org/collision-detection/line-line.php ---- detekcia kolízií medzi dvomi čiarami
void RelationGraphicsObject::LineRectCollision(QPointF*, QLineF, QRectF) ----  http://jeffreythompson.org/collision-detection/line-rect.php ---- detekcia kolízií medzi čiarou a obdĺžnikom
