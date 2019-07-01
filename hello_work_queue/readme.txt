tasklet的示例

journalctl -f

make

sudo insmod hello.ko

sudo rmmod hello

make clean

在hello_tasklet_func()中的调用msleep()会导致系统内核报错，如下
Jul  1 14:59:33 ub18 kernel: [75441.579979] Hello, world
Jul  1 14:59:33 ub18 kernel: [75441.579987] BUG: scheduling while atomic: ksoftirqd/0/7/0x00000100
Jul  1 14:59:33 ub18 kernel: [75441.579989] Modules linked in: hello(OE) snd_intel8x0 snd_ac97_codec ac97_bus snd_pcm snd_seq_midi snd_seq_midi_event intel_powerclamp crct10dif_pclmul crc32_pclmul ghash_clmulni_intel pcbc snd_rawmidi aesni_intel aes_x86_64 crypto_simd glue_helper cryptd intel_rapl_perf snd_seq joydev snd_seq_device snd_timer input_leds vboxvideo(CE) serio_raw ttm snd drm_kms_helper drm fb_sys_fops syscopyarea vboxguest soundcore sysfillrect sysimgblt mac_hid sch_fq_codel parport_pc ppdev lp parport ip_tables x_tables autofs4 hid_generic usbhid hid psmouse ahci libahci i2c_piix4 e1000 pata_acpi video [last unloaded: hello]
Jul  1 14:59:33 ub18 kernel: [75441.580037] CPU: 0 PID: 7 Comm: ksoftirqd/0 Tainted: G         C OE    4.15.0-32-generic #35-Ubuntu
Jul  1 14:59:33 ub18 kernel: [75441.580039] Hardware name: innotek GmbH VirtualBox/VirtualBox, BIOS VirtualBox 12/01/2006
Jul  1 14:59:33 ub18 kernel: [75441.580040] Call Trace:
Jul  1 14:59:33 ub18 kernel: [75441.580047]  dump_stack+0x63/0x8b
Jul  1 14:59:33 ub18 kernel: [75441.580050]  __schedule_bug+0x55/0x70
Jul  1 14:59:33 ub18 kernel: [75441.580052]  __schedule+0x5fd/0x8a0
Jul  1 14:59:33 ub18 kernel: [75441.580054]  ? __switch_to_asm+0x40/0x70
Jul  1 14:59:33 ub18 kernel: [75441.580055]  ? __switch_to_asm+0x40/0x70
Jul  1 14:59:33 ub18 kernel: [75441.580057]  schedule+0x2c/0x80
Jul  1 14:59:33 ub18 kernel: [75441.580058]  schedule_timeout+0x15d/0x350
Jul  1 14:59:33 ub18 kernel: [75441.580060]  ? __next_timer_interrupt+0xe0/0xe0
Jul  1 14:59:33 ub18 kernel: [75441.580062]  msleep+0x2d/0x40
Jul  1 14:59:33 ub18 kernel: [75441.580064]  hello_tasklet_func+0x12/0x2b [hello]
Jul  1 14:59:33 ub18 kernel: [75441.580066]  tasklet_action+0x64/0x110
Jul  1 14:59:33 ub18 kernel: [75441.580068]  __do_softirq+0xe4/0x2bb
Jul  1 14:59:33 ub18 kernel: [75441.580069]  run_ksoftirqd+0x22/0x60
Jul  1 14:59:33 ub18 kernel: [75441.580071]  smpboot_thread_fn+0xfc/0x170
Jul  1 14:59:33 ub18 kernel: [75441.580073]  kthread+0x121/0x140
Jul  1 14:59:33 ub18 kernel: [75441.580074]  ? sort_range+0x30/0x30
Jul  1 14:59:33 ub18 kernel: [75441.580076]  ? kthread_create_worker_on_cpu+0x70/0x70
Jul  1 14:59:33 ub18 kernel: [75441.580077]  ret_from_fork+0x35/0x40
Jul  1 14:59:34 ub18 kernel: [75442.612217] hello_tasklet_func, data=1000
Jul  1 14:59:34 ub18 kernel: [75442.612232] softirq: huh, entered softirq 6 TASKLET 00000000f8716ea3 with preempt_count 00000100, exited with 00000000?
