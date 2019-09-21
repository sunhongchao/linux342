
#define SECOND_MAJOR 252 /*预设的 second 的主设备号*/

static int second_major = SECOND_MAJOR;
6
7 /*second 设备结构体*/
8 struct second_dev
9 {
10 struct cdev cdev; /*cdev 结构体*/
11 atomic_t counter;/* 一共经历了多少秒？ */
12 struct timer_list s_timer; /*设备要使用的定时器*/
13 };
14
15 struct second_dev *second_devp; /*设备结构体指针*/
16
17 /*定时器处理函数*/
18 static void second_timer_handle(unsigned long arg)
19 {
20 mod_timer(&second_devp->s_timer,jiffies + HZ);
21 atomic_inc(&second_devp->counter);
22
23 printk(KERN_NOTICE "current jiffies is %ld\n", jiffies);
24 }
25
26 /*文件打开函数*/
27 int second_open(struct inode *inode, struct file *filp)
28 {
29 /*初始化定时器*/
30 init_timer(&second_devp->s_timer);
31 second_devp->s_timer.function = &second_timer_handle;
32 second_devp->s_timer.expires = jiffies + HZ;
33
34 add_timer(&second_devp->s_timer); /*添加（注册）定时器*/
35
36 atomic_set(&second_devp->counter,0); //计数清零
37
38 return 0;
39 }
40 /*文件释放函数*/
41 int second_release(struct inode *inode, struct file *filp)
42 {
43 del_timer(&second_devp->s_timer);
44
45 return 0;
46 }
47
48 /*globalfifo 读函数*/
49 static ssize_t second_read(struct file *filp, char _ _user *buf, size_t count,
50 loff_t *ppos)























