There is nice online font editor: http://www.pentacom.jp/pentacom/bitfontmaker2/

Thank you very much, guys!

I make this simple tool on java for creating header file for your own font.

usage:

1. Paint (or load previous saved) you own Unicode font in the [BitFontMaker2](http://www.pentacom.jp/pentacom/bitfontmaker2)
2. Save it in a file. For example, it has name `font.json`
3. Go directly in to the pentacom-font folder
4. Compile `javac -Xlint:unchecked ./me/lakhtin/Main`
5. Run `java me.lakhtin.Main ./font.json > myfontname.h`