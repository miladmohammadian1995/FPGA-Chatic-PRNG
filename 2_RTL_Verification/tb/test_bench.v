`timescale 1ns / 1ps

module prng_tb;

    // Parameters
    localparam CLK_PERIOD = 10; // 100 MHz clock

    // Inputs for prng_generator
    reg ap_clk;
    reg ap_rst_n;
    reg s_axi_control_AWVALID;
    reg [5:0] s_axi_control_AWADDR;
    reg s_axi_control_WVALID;
    reg [31:0] s_axi_control_WDATA;
    reg out_stream_TREADY;

    // Outputs from prng_generator
    wire s_axi_control_AWREADY;
    wire s_axi_control_WREADY;
    wire [7:0] out_stream_TDATA;
    wire out_stream_TVALID;
    wire [0:0] out_stream_TLAST;

    // Instantiate the PRNG Generator IP
    // این بخش به طور کامل با پورت‌های شما اصلاح شده است
    prng_generator prng_inst (
        .ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),

        // AXI-Lite Write Address Channel
        .s_axi_control_AWVALID(s_axi_control_AWVALID),
        .s_axi_control_AWREADY(s_axi_control_AWREADY),
        .s_axi_control_AWADDR(s_axi_control_AWADDR),

        // AXI-Lite Write Data Channel
        .s_axi_control_WVALID(s_axi_control_WVALID),
        .s_axi_control_WREADY(s_axi_control_WREADY),
        .s_axi_control_WDATA(s_axi_control_WDATA),

        // AXI-Stream Output
        .out_stream_TDATA(out_stream_TDATA),
        .out_stream_TVALID(out_stream_TVALID),
        .out_stream_TREADY(out_stream_TREADY),
        .out_stream_TLAST(out_stream_TLAST)

        // سایر پورت‌های استفاده نشده به صورت خودکار باز می‌مانند
    );

    // Clock generation
    initial begin
        ap_clk = 0;
        forever #(CLK_PERIOD/2) ap_clk = ~ap_clk;
    end

    // Test sequence
    initial begin
        // 1. Reset the system
        ap_rst_n = 0;
        s_axi_control_AWVALID = 0;
        s_axi_control_WVALID = 0;
        s_axi_control_AWADDR = 0;
        s_axi_control_WDATA = 0;
        out_stream_TREADY = 1'b1; // مهم: تست‌بنچ همیشه آماده دریافت داده است
        # (CLK_PERIOD * 10);
        ap_rst_n = 1;
        # (CLK_PERIOD);

        // 2. Write seed (Address 0x10 for 'seed')
        s_axi_control_AWADDR = 6'h10;
        s_axi_control_WDATA  = 64'h3fe8000000000000; // Seed = 0.75
        s_axi_control_AWVALID = 1;
        s_axi_control_WVALID = 1;
        wait(s_axi_control_AWREADY && s_axi_control_WREADY);
        # (CLK_PERIOD);
        s_axi_control_AWVALID = 0;
        s_axi_control_WVALID = 0;

        // 3. Write n_bits (Address 0x1C for 'n_bits')
        s_axi_control_AWADDR = 6'h1C;
        s_axi_control_WDATA  = 32'd5; // n_bits = 5
        s_axi_control_AWVALID = 1;
        s_axi_control_WVALID = 1;
        wait(s_axi_control_AWREADY && s_axi_control_WREADY);
        # (CLK_PERIOD);
        s_axi_control_AWVALID = 0;
        s_axi_control_WVALID = 0;

        // 4. Write num_bits (Address 0x24 for 'num_bits')
        s_axi_control_AWADDR = 6'h24;
        s_axi_control_WDATA  = 32'd100; // Generate 100 bits
        s_axi_control_AWVALID = 1;
        s_axi_control_WVALID = 1;
        wait(s_axi_control_AWREADY && s_axi_control_WREADY);
        # (CLK_PERIOD);
        s_axi_control_AWVALID = 0;
        s_axi_control_WVALID = 0;

        // 5. Start the IP core (Write 1 to ap_start at Address 0x00)
        s_axi_control_AWADDR = 6'h00;
        s_axi_control_WDATA  = 32'h01; // ap_start
        s_axi_control_AWVALID = 1;
        s_axi_control_WVALID = 1;
        wait(s_axi_control_AWREADY && s_axi_control_WREADY);
        # (CLK_PERIOD);
        s_axi_control_AWVALID = 0;
        s_axi_control_WVALID = 0;

        // Wait for the process to finish (TLAST signal)
        wait(out_stream_TLAST);
        # (CLK_PERIOD * 20);

        // End simulation
        $finish;
    end

endmodule