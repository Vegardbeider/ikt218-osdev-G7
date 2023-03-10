const Console = @import("Console.zig");
const isr = @import("../isr.zig");
const utils = @import("../utils.zig");

// Keyboard state
var lshift = false;

fn handler(_: isr.Registers) void {
    const scancode = utils.inb(0x60);
    switch (scancode) {
        0x10 => if (lshift) Console.write("Q") else Console.write("q"),
        0x11 => if (lshift) Console.write("W") else Console.write("w"),
        0x12 => if (lshift) Console.write("E") else Console.write("e"),
        0x13 => if (lshift) Console.write("R") else Console.write("r"),
        0x14 => if (lshift) Console.write("T") else Console.write("t"),
        0x15 => if (lshift) Console.write("Y") else Console.write("y"),
        0x16 => if (lshift) Console.write("U") else Console.write("u"),
        0x17 => if (lshift) Console.write("I") else Console.write("i"),
        0x18 => if (lshift) Console.write("O") else Console.write("o"),
        0x19 => if (lshift) Console.write("P") else Console.write("p"),
        0x1E => if (lshift) Console.write("A") else Console.write("a"),
        0x1F => if (lshift) Console.write("S") else Console.write("s"),
        0x20 => if (lshift) Console.write("D") else Console.write("d"),
        0x21 => if (lshift) Console.write("F") else Console.write("f"),
        0x22 => if (lshift) Console.write("G") else Console.write("g"),
        0x23 => if (lshift) Console.write("H") else Console.write("h"),
        0x24 => if (lshift) Console.write("J") else Console.write("j"),
        0x25 => if (lshift) Console.write("K") else Console.write("k"),
        0x26 => if (lshift) Console.write("L") else Console.write("l"),
        0x2C => if (lshift) Console.write("Z") else Console.write("z"),
        0x2D => if (lshift) Console.write("X") else Console.write("x"),
        0x2E => if (lshift) Console.write("C") else Console.write("c"),
        0x2F => if (lshift) Console.write("V") else Console.write("v"),
        0x30 => if (lshift) Console.write("B") else Console.write("b"),
        0x31 => if (lshift) Console.write("N") else Console.write("n"),
        0x32 => if (lshift) Console.write("M") else Console.write("m"),
        0x39 => Console.write(" "),
        0x1C => Console.write("\n"),
        0x2A => lshift = true,
        0xAA => lshift = false,
        else => {},
    }
}

pub fn init() void {
    isr.setHandler(isr.IRQ1, handler);
    utils.outb(0x21, 0xFD);
    utils.outb(0xA1, 0xFF);
}
