package me.lakhtin;

import java.io.IOException;
import java.nio.file.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.regex.*;
import java.util.stream.Stream;

public class Main {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.print("You should point input filename");
            System.exit(1);
        }

        System.out.println("\n\r//" +
                "\n\r// it was generated automatically from file: " + args[0]  +
                "\n\r// Note: save it with different name to avoid a lost" +
                "\n\r\n\r" +
                "\n\r#ifndef PENTACOM_FONT" +
                "\n\r#define PENTACOM_FONT" +
                "\n\r\n" +
                "\ntypedef struct {" +
                "\n\ruint8_t size;"+
                "\n\ruint8_t l[];"+
                "\n\r} FontChar_t;\n\r");

        System.out.println("\n\rconst FontChar_t spaceChar = {2, {0x00, 0x00}};");

        Pattern pattern = Pattern.compile("[\"]*[0-9]{2,4}[\"]*");
        int pos = 0;
        ArrayList charSet = new ArrayList();
        try (Stream<String> stream = Files.lines(Paths.get(args[0]))) {

            stream
                    .flatMap(p -> Arrays.stream(p.split("],")))
                    .filter(l -> l.contains(":["))
                    .forEach(s -> {
                        System.out.println("\n// original was " + s);
                        Matcher m = pattern.matcher(s);
                        if (!m.find()) {
                            System.err.print("Parse error");
                            System.exit(2);
                        }
                        String id = s.substring(m.start(), m.end()).replace("\"", "");
                        System.out.print("const FontChar_t char_" + id + "=");
                        String[] nums = s.substring(s.indexOf("[") + 1).split(",");
                        ArrayList<Short> b = new ArrayList<Short>();
                        int i = 0;
                        boolean longVal = false;
                        ArrayList<Short> res = new ArrayList<Short>();
                        for (String val : nums) {
                            b.add(i, Short.parseShort(val));
                            i++;
                        }
                        short buffer[] = new short[8];
                        int depth = 0;
                        for (i = 0; i < 8; ++i)
                            buffer[i] = 0;
                        if (b.size() < 8) {
                            for (i = 0; i < 8 - b.size(); i++)
                                b.add(Short.valueOf("0"));
                        }
                        while (depth < 8) {
                            for (i = 0; i < 8; i++) {
                                short vv = b.get(i).shortValue();
                                if (vv > 255)
                                    longVal = true;
                                short vb = (short) ((vv & 0x00ff & (1 << 7 - depth)) >> (7 - depth));
                                if (vb == 0)
                                    continue;
                                buffer[7 - depth] |= vb << i;
                            }
                            depth++;
                        }
                        for (short val : buffer) {
                            res.add(val);
                        }

                        if (longVal) {
                            for (i = 0; i < 8; ++i)
                                buffer[i] = 0;
                            depth = 0;
                            for (i = 0; i < 8; i++) {
                                while (depth < 8) {
                                    for (i = 0; i < 8; i++) {
                                        short vv = (short) (b.get(i).shortValue() >> 8);
                                        short vb = (short) ((vv & (1 << 7 - depth)) >> (7 - depth));
                                        if (vb == 0)
                                            continue;
                                        buffer[7 - depth] |= vb << i;
                                    }
                                    depth++;
                                }
                            }

                            for (short val : buffer) {
                                res.add(val);
                            }
                        }


                        int cnt = res.size();
                        for (i = res.size() - 1; i >= 0; i--) {
                            if (res.get(i).shortValue() == 0) {
                                cnt = i;
                            } else
                                break;
                        }

                        System.out.print("{" + cnt + ", {");

                        for (i = 0; i < cnt; ++i) {
                            System.out.print(hex(res.get(i)));
                            if (i < (cnt - 1))
                                System.out.print(",");
                            else
                                System.out.println("}}; // " + new Character((char) Short.parseShort(id)).toString());
                        }

                        charSet.add(id);

                    });

            System.out.println("\n\r\n\rconst uint16_t charTableSize = "+charSet.size()+";");
            System.out.println("\n\r\n\rconst uint16_t charTable[] = {");
            int i = 0;
            String chs = "";
            int divider = 16;
            for (Object val : charSet) {
                if (i % divider == 0) {
                    chs = "// ";
                    System.out.print("\t\t");
                }

                System.out.print(val);
                chs += new Character((char) Short.parseShort(val.toString())).toString() + ", ";
                i++;
                if (i < charSet.size())
                    System.out.print(",");
                else
                    System.out.println("};");
                if (i % divider == 0)
                    System.out.println(chs);
            }

            divider = 12;
            i = 0;

            System.out.println("\n\r\n\rconst FontChar_t* chars[] = {");
            for (Object val : charSet) {
                if (i % divider == 0) {
                    System.out.print("\t\t");
                }
                System.out.print(" &char_" + val);
                i++;
                if (i < charSet.size())
                    System.out.print(",");
                else
                    System.out.println("};");
                if (i % divider == 0) {
                    System.out.println();
                }
            }

            System.out.println("\n" +
                    "#endif //PENTACOM_FONT" +
                    "\n\r// end of file");


        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static short Invert(short x) {
        int base = 256;

        int res = 0;
        while (x != 0) {
            res += (x & 1) * (base >>= 1);
            x >>= 1;
        }

        return (short) res;
    }

    public static String hex(short n) {
        // call toUpperCase() if that's required
        return String.format("0x%2s", Integer.toHexString(n)).replace(' ', '0');
    }

}

