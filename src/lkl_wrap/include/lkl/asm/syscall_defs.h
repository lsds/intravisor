#ifdef __lkl__NR_virtio_mmio_device_add
LKL_SYSCALL_DEFINE3(_virtio_mmio_device_add,long,base,long,size,unsigned int,irq)
#endif
#ifdef __lkl__NR_set_tid_address
LKL_SYSCALL_DEFINE1(_set_tid_address,int *,tidptr)
#endif
#ifdef __lkl__NR_clone
LKL_SYSCALL_DEFINE5(_clone,unsigned long,clone_flags,unsigned long,newsp,int *,parent_tidptr,int *,child_tidptr,unsigned long,tls)
#endif
#ifdef __lkl__NR_unshare
LKL_SYSCALL_DEFINE1(_unshare,unsigned long,unshare_flags)
#endif
#ifdef __lkl__NR_personality
LKL_SYSCALL_DEFINE1(_personality,unsigned int,personality)
#endif
#ifdef __lkl__NR_exit
LKL_SYSCALL_DEFINE1(_exit,int,error_code)
#endif
#ifdef __lkl__NR_exit_group
LKL_SYSCALL_DEFINE1(_exit_group,int,error_code)
#endif
#ifdef __lkl__NR_waitid
LKL_SYSCALL_DEFINE5(_waitid,int,which,lkl_pid_t,upid,struct lkl_siginfo *,infop,int,options,struct lkl_rusage *,ru)
#endif
#ifdef __lkl__NR_wait4
LKL_SYSCALL_DEFINE4(_wait4,lkl_pid_t,upid,int *,stat_addr,int,options,struct lkl_rusage *,ru)
#endif
#ifdef __NR_sysctl
LKL_SYSCALL_DEFINE1(_sysctl,struct __sysctl_args *,args)
#endif
#ifdef __lkl__NR_capget
LKL_SYSCALL_DEFINE2(_capget,lkl_cap_user_header_t,header,lkl_cap_user_data_t,dataptr)
#endif
#ifdef __lkl__NR_capset
LKL_SYSCALL_DEFINE2(_capset,lkl_cap_user_header_t,header,const lkl_cap_user_data_t,data)
#endif
#ifdef __lkl__NR_ptrace
LKL_SYSCALL_DEFINE4(_ptrace,long,request,long,pid,unsigned long,addr,unsigned long,data)
#endif
#ifdef __lkl__NR_restart_syscall
LKL_SYSCALL_DEFINE0(_restart_syscall,)
#endif
#ifdef __lkl__NR_rt_sigprocmask
LKL_SYSCALL_DEFINE4(_rt_sigprocmask,int,how,lkl_sigset_t *,nset,lkl_sigset_t *,oset,lkl_size_t,sigsetsize)
#endif
#ifdef __lkl__NR_rt_sigpending
LKL_SYSCALL_DEFINE2(_rt_sigpending,lkl_sigset_t *,uset,lkl_size_t,sigsetsize)
#endif
#ifdef __lkl__NR_rt_sigtimedwait
LKL_SYSCALL_DEFINE4(_rt_sigtimedwait,const lkl_sigset_t *,uthese,lkl_siginfo_t *,uinfo,const struct lkl_timespec *,uts,lkl_size_t,sigsetsize)
#endif
#ifdef __lkl__NR_kill
LKL_SYSCALL_DEFINE2(_kill,lkl_pid_t,pid,int,sig)
#endif
#ifdef __lkl__NR_tgkill
LKL_SYSCALL_DEFINE3(_tgkill,lkl_pid_t,tgid,lkl_pid_t,pid,int,sig)
#endif
#ifdef __lkl__NR_tkill
LKL_SYSCALL_DEFINE2(_tkill,lkl_pid_t,pid,int,sig)
#endif
#ifdef __lkl__NR_rt_sigqueueinfo
LKL_SYSCALL_DEFINE3(_rt_sigqueueinfo,lkl_pid_t,pid,int,sig,lkl_siginfo_t *,uinfo)
#endif
#ifdef __lkl__NR_rt_tgsigqueueinfo
LKL_SYSCALL_DEFINE4(_rt_tgsigqueueinfo,lkl_pid_t,tgid,lkl_pid_t,pid,int,sig,lkl_siginfo_t *,uinfo)
#endif
#ifdef __lkl__NR_sigaltstack
LKL_SYSCALL_DEFINE2(_sigaltstack,const lkl_stack_t *,uss,lkl_stack_t *,uoss)
#endif
#ifdef __lkl__NR_rt_sigaction
LKL_SYSCALL_DEFINE4(_rt_sigaction,int,sig,const struct lkl_sigaction *,act,struct lkl_sigaction *,oact,lkl_size_t,sigsetsize)
#endif
#ifdef __lkl__NR_rt_sigsuspend
LKL_SYSCALL_DEFINE2(_rt_sigsuspend,lkl_sigset_t *,unewset,lkl_size_t,sigsetsize)
#endif
#ifdef __lkl__NR_setpriority
LKL_SYSCALL_DEFINE3(_setpriority,int,which,int,who,int,niceval)
#endif
#ifdef __lkl__NR_getpriority
LKL_SYSCALL_DEFINE2(_getpriority,int,which,int,who)
#endif
#ifdef __lkl__NR_setregid
LKL_SYSCALL_DEFINE2(_setregid,lkl_gid_t,rgid,lkl_gid_t,egid)
#endif
#ifdef __lkl__NR_setgid
LKL_SYSCALL_DEFINE1(_setgid,lkl_gid_t,gid)
#endif
#ifdef __lkl__NR_setreuid
LKL_SYSCALL_DEFINE2(_setreuid,lkl_uid_t,ruid,lkl_uid_t,euid)
#endif
#ifdef __lkl__NR_setuid
LKL_SYSCALL_DEFINE1(_setuid,lkl_uid_t,uid)
#endif
#ifdef __lkl__NR_setresuid
LKL_SYSCALL_DEFINE3(_setresuid,lkl_uid_t,ruid,lkl_uid_t,euid,lkl_uid_t,suid)
#endif
#ifdef __lkl__NR_getresuid
LKL_SYSCALL_DEFINE3(_getresuid,lkl_uid_t *,ruidp,lkl_uid_t *,euidp,lkl_uid_t *,suidp)
#endif
#ifdef __lkl__NR_setresgid
LKL_SYSCALL_DEFINE3(_setresgid,lkl_gid_t,rgid,lkl_gid_t,egid,lkl_gid_t,sgid)
#endif
#ifdef __lkl__NR_getresgid
LKL_SYSCALL_DEFINE3(_getresgid,lkl_gid_t *,rgidp,lkl_gid_t *,egidp,lkl_gid_t *,sgidp)
#endif
#ifdef __lkl__NR_setfsuid
LKL_SYSCALL_DEFINE1(_setfsuid,lkl_uid_t,uid)
#endif
#ifdef __lkl__NR_setfsgid
LKL_SYSCALL_DEFINE1(_setfsgid,lkl_gid_t,gid)
#endif
#ifdef __lkl__NR_getpid
LKL_SYSCALL_DEFINE0(_getpid,)
#endif
#ifdef __lkl__NR_gettid
LKL_SYSCALL_DEFINE0(_gettid,)
#endif
#ifdef __lkl__NR_getppid
LKL_SYSCALL_DEFINE0(_getppid,)
#endif
#ifdef __lkl__NR_getuid
LKL_SYSCALL_DEFINE0(_getuid,)
#endif
#ifdef __lkl__NR_geteuid
LKL_SYSCALL_DEFINE0(_geteuid,)
#endif
#ifdef __lkl__NR_getgid
LKL_SYSCALL_DEFINE0(_getgid,)
#endif
#ifdef __lkl__NR_getegid
LKL_SYSCALL_DEFINE0(_getegid,)
#endif
#ifdef __lkl__NR_times
LKL_SYSCALL_DEFINE1(_times,struct lkl_tms *,tbuf)
#endif
#ifdef __lkl__NR_setpgid
LKL_SYSCALL_DEFINE2(_setpgid,lkl_pid_t,pid,lkl_pid_t,pgid)
#endif
#ifdef __lkl__NR_getpgid
LKL_SYSCALL_DEFINE1(_getpgid,lkl_pid_t,pid)
#endif
#ifdef __lkl__NR_getsid
LKL_SYSCALL_DEFINE1(_getsid,lkl_pid_t,pid)
#endif
#ifdef __lkl__NR_setsid
LKL_SYSCALL_DEFINE0(_setsid,)
#endif
#ifdef __NR_newuname
LKL_SYSCALL_DEFINE1(_newuname,struct new_utsname *,name)
#endif
#ifdef __lkl__NR_sethostname
LKL_SYSCALL_DEFINE2(_sethostname,char *,name,int,len)
#endif
#ifdef __lkl__NR_setdomainname
LKL_SYSCALL_DEFINE2(_setdomainname,char *,name,int,len)
#endif
#ifdef __lkl__NR_getrlimit
LKL_SYSCALL_DEFINE2(_getrlimit,unsigned int,resource,struct lkl_rlimit *,rlim)
#endif
#ifdef __lkl__NR_prlimit64
LKL_SYSCALL_DEFINE4(_prlimit64,lkl_pid_t,pid,unsigned int,resource,const struct lkl_rlimit64 *,new_rlim,struct lkl_rlimit64 *,old_rlim)
#endif
#ifdef __lkl__NR_setrlimit
LKL_SYSCALL_DEFINE2(_setrlimit,unsigned int,resource,struct lkl_rlimit *,rlim)
#endif
#ifdef __lkl__NR_getrusage
LKL_SYSCALL_DEFINE2(_getrusage,int,who,struct lkl_rusage *,ru)
#endif
#ifdef __lkl__NR_umask
LKL_SYSCALL_DEFINE1(_umask,int,mask)
#endif
#ifdef __lkl__NR_prctl
LKL_SYSCALL_DEFINE5(_prctl,int,option,unsigned long,arg2,unsigned long,arg3,unsigned long,arg4,unsigned long,arg5)
#endif
#ifdef __lkl__NR_getcpu
LKL_SYSCALL_DEFINE3(_getcpu,unsigned *,cpup,unsigned *,nodep,struct getcpu_cache *,unused)
#endif
#ifdef __lkl__NR_sysinfo
LKL_SYSCALL_DEFINE1(_sysinfo,struct lkl_sysinfo *,info)
#endif
#ifdef __lkl__NR_setns
LKL_SYSCALL_DEFINE2(_setns,int,fd,int,nstype)
#endif
#ifdef __lkl__NR_reboot
LKL_SYSCALL_DEFINE4(_reboot,int,magic1,int,magic2,unsigned int,cmd,void *,arg)
#endif
#ifdef __lkl__NR_getgroups
LKL_SYSCALL_DEFINE2(_getgroups,int,gidsetsize,lkl_gid_t *,grouplist)
#endif
#ifdef __lkl__NR_setgroups
LKL_SYSCALL_DEFINE2(_setgroups,int,gidsetsize,lkl_gid_t *,grouplist)
#endif
#ifdef __lkl__NR_sched_setscheduler
LKL_SYSCALL_DEFINE3(_sched_setscheduler,lkl_pid_t,pid,int,policy,struct sched_param *,param)
#endif
#ifdef __lkl__NR_sched_setparam
LKL_SYSCALL_DEFINE2(_sched_setparam,lkl_pid_t,pid,struct sched_param *,param)
#endif
#ifdef __lkl__NR_sched_setattr
LKL_SYSCALL_DEFINE3(_sched_setattr,lkl_pid_t,pid,struct sched_attr *,uattr,unsigned int,flags)
#endif
#ifdef __lkl__NR_sched_getscheduler
LKL_SYSCALL_DEFINE1(_sched_getscheduler,lkl_pid_t,pid)
#endif
#ifdef __lkl__NR_sched_getparam
LKL_SYSCALL_DEFINE2(_sched_getparam,lkl_pid_t,pid,struct sched_param *,param)
#endif
#ifdef __lkl__NR_sched_getattr
LKL_SYSCALL_DEFINE4(_sched_getattr,lkl_pid_t,pid,struct sched_attr *,uattr,unsigned int,size,unsigned int,flags)
#endif
#ifdef __lkl__NR_sched_setaffinity
LKL_SYSCALL_DEFINE3(_sched_setaffinity,lkl_pid_t,pid,unsigned int,len,unsigned long *,user_mask_ptr)
#endif
#ifdef __lkl__NR_sched_getaffinity
LKL_SYSCALL_DEFINE3(_sched_getaffinity,lkl_pid_t,pid,unsigned int,len,unsigned long *,user_mask_ptr)
#endif
#ifdef __lkl__NR_sched_yield
LKL_SYSCALL_DEFINE0(_sched_yield,)
#endif
#ifdef __lkl__NR_sched_get_priority_max
LKL_SYSCALL_DEFINE1(_sched_get_priority_max,int,policy)
#endif
#ifdef __lkl__NR_sched_get_priority_min
LKL_SYSCALL_DEFINE1(_sched_get_priority_min,int,policy)
#endif
#ifdef __lkl__NR_sched_rr_get_interval
LKL_SYSCALL_DEFINE2(_sched_rr_get_interval,lkl_pid_t,pid,struct lkl_timespec *,interval)
#endif
#ifdef __lkl__NR_membarrier
LKL_SYSCALL_DEFINE2(_membarrier,int,cmd,int,flags)
#endif
#ifdef __lkl__NR_syslog
LKL_SYSCALL_DEFINE3(_syslog,int,type,char *,buf,int,len)
#endif
#ifdef __lkl__NR_gettimeofday
LKL_SYSCALL_DEFINE2(_gettimeofday,struct lkl_timeval *,tv,struct lkl_timezone *,tz)
#endif
#ifdef __lkl__NR_settimeofday
LKL_SYSCALL_DEFINE2(_settimeofday,struct lkl_timeval *,tv,struct lkl_timezone *,tz)
#endif
#ifdef __lkl__NR_adjtimex
LKL_SYSCALL_DEFINE1(_adjtimex,struct lkl_timex *,txc_p)
#endif
#ifdef __lkl__NR_nanosleep
LKL_SYSCALL_DEFINE2(_nanosleep,struct lkl_timespec *,rqtp,struct lkl_timespec *,rmtp)
#endif
#ifdef __lkl__NR_timer_create
LKL_SYSCALL_DEFINE3(_timer_create,const lkl_clockid_t,which_clock,struct lkl_sigevent *,timer_event_spec,lkl_timer_t *,created_timer_id)
#endif
#ifdef __lkl__NR_timer_gettime
LKL_SYSCALL_DEFINE2(_timer_gettime,lkl_timer_t,timer_id,struct lkl_itimerspec *,setting)
#endif
#ifdef __lkl__NR_timer_getoverrun
LKL_SYSCALL_DEFINE1(_timer_getoverrun,lkl_timer_t,timer_id)
#endif
#ifdef __lkl__NR_timer_settime
LKL_SYSCALL_DEFINE4(_timer_settime,lkl_timer_t,timer_id,int,flags,const struct lkl_itimerspec *,new_setting,struct lkl_itimerspec *,old_setting)
#endif
#ifdef __lkl__NR_timer_delete
LKL_SYSCALL_DEFINE1(_timer_delete,lkl_timer_t,timer_id)
#endif
#ifdef __lkl__NR_clock_settime
LKL_SYSCALL_DEFINE2(_clock_settime,const lkl_clockid_t,which_clock,const struct lkl_timespec *,tp)
#endif
#ifdef __lkl__NR_clock_gettime
LKL_SYSCALL_DEFINE2(_clock_gettime,const lkl_clockid_t,which_clock,struct lkl_timespec *,tp)
#endif
#ifdef __lkl__NR_clock_adjtime
LKL_SYSCALL_DEFINE2(_clock_adjtime,const lkl_clockid_t,which_clock,struct lkl_timex *,utx)
#endif
#ifdef __lkl__NR_clock_getres
LKL_SYSCALL_DEFINE2(_clock_getres,const lkl_clockid_t,which_clock,struct lkl_timespec *,tp)
#endif
#ifdef __lkl__NR_clock_nanosleep
LKL_SYSCALL_DEFINE4(_clock_nanosleep,const lkl_clockid_t,which_clock,int,flags,const struct lkl_timespec *,rqtp,struct lkl_timespec *,rmtp)
#endif
#ifdef __lkl__NR_getitimer
LKL_SYSCALL_DEFINE2(_getitimer,int,which,struct lkl_itimerval *,value)
#endif
#ifdef __lkl__NR_setitimer
LKL_SYSCALL_DEFINE3(_setitimer,int,which,struct lkl_itimerval *,value,struct lkl_itimerval *,ovalue)
#endif
#ifdef __lkl__NR_init_module
LKL_SYSCALL_DEFINE3(_init_module,void *,umod,unsigned long,len,const char *,uargs)
#endif
#ifdef __lkl__NR_finit_module
LKL_SYSCALL_DEFINE3(_finit_module,int,fd,const char *,uargs,int,flags)
#endif
#ifdef __lkl__NR_readahead
LKL_SYSCALL_DEFINE3(_readahead,int,fd,lkl_loff_t,offset,lkl_size_t,count)
#endif
#ifdef __lkl__NR_brk
LKL_SYSCALL_DEFINE1(_brk,unsigned long,brk)
#endif
#ifdef __lkl__NR_mmap_pgoff
LKL_SYSCALL_DEFINE6(_mmap_pgoff,unsigned long,addr,unsigned long,len,unsigned long,prot,unsigned long,flags,unsigned long,fd,unsigned long,pgoff)
#endif
#ifdef __lkl__NR_munmap
LKL_SYSCALL_DEFINE2(_munmap,unsigned long,addr,lkl_size_t,len)
#endif
#ifdef __lkl__NR_mremap
LKL_SYSCALL_DEFINE5(_mremap,unsigned long,addr,unsigned long,old_len,unsigned long,new_len,unsigned long,flags,unsigned long,new_addr)
#endif
#ifdef __lkl__NR_fadvise64_64
LKL_SYSCALL_DEFINE4(_fadvise64_64,int,fd,lkl_loff_t,offset,lkl_loff_t,len,int,advice)
#endif
#ifdef __lkl__NR_truncate
LKL_SYSCALL_DEFINE2(_truncate,const char *,path,long,length)
#endif
#ifdef __lkl__NR_ftruncate
LKL_SYSCALL_DEFINE2(_ftruncate,unsigned int,fd,unsigned long,length)
#endif
#ifdef __lkl__NR_fallocate
LKL_SYSCALL_DEFINE4(_fallocate,int,fd,int,mode,lkl_loff_t,offset,lkl_loff_t,len)
#endif
#ifdef __lkl__NR_faccessat
LKL_SYSCALL_DEFINE3(_faccessat,int,dfd,const char *,filename,int,mode)
#endif
#ifdef __NR_access
LKL_SYSCALL_DEFINE2(_access,const char *,filename,int,mode)
#endif
#ifdef __lkl__NR_chdir
LKL_SYSCALL_DEFINE1(_chdir,const char *,filename)
#endif
#ifdef __lkl__NR_fchdir
LKL_SYSCALL_DEFINE1(_fchdir,unsigned int,fd)
#endif
#ifdef __lkl__NR_chroot
LKL_SYSCALL_DEFINE1(_chroot,const char *,filename)
#endif
#ifdef __lkl__NR_fchmod
LKL_SYSCALL_DEFINE2(_fchmod,unsigned int,fd,lkl_umode_t,mode)
#endif
#ifdef __lkl__NR_fchmodat
LKL_SYSCALL_DEFINE3(_fchmodat,int,dfd,const char *,filename,lkl_umode_t,mode)
#endif
#ifdef __NR_chmod
LKL_SYSCALL_DEFINE2(_chmod,const char *,filename,lkl_umode_t,mode)
#endif
#ifdef __lkl__NR_fchownat
LKL_SYSCALL_DEFINE5(_fchownat,int,dfd,const char *,filename,lkl_uid_t,user,lkl_gid_t,group,int,flag)
#endif
#ifdef __NR_chown
LKL_SYSCALL_DEFINE3(_chown,const char *,filename,lkl_uid_t,user,lkl_gid_t,group)
#endif
#ifdef __NR_lchown
LKL_SYSCALL_DEFINE3(_lchown,const char *,filename,lkl_uid_t,user,lkl_gid_t,group)
#endif
#ifdef __lkl__NR_fchown
LKL_SYSCALL_DEFINE3(_fchown,unsigned int,fd,lkl_uid_t,user,lkl_gid_t,group)
#endif
#ifdef __NR_open
LKL_SYSCALL_DEFINE3(_open,const char *,filename,int,flags,lkl_umode_t,mode)
#endif
#ifdef __lkl__NR_openat
LKL_SYSCALL_DEFINE4(_openat,int,dfd,const char *,filename,int,flags,lkl_umode_t,mode)
#endif
#ifdef __NR_creat
LKL_SYSCALL_DEFINE2(_creat,const char *,pathname,lkl_umode_t,mode)
#endif
#ifdef __lkl__NR_close
LKL_SYSCALL_DEFINE1(_close,unsigned int,fd)
#endif
#ifdef __lkl__NR_vhangup
LKL_SYSCALL_DEFINE0(_vhangup,)
#endif
#ifdef __lkl__NR_lseek
LKL_SYSCALL_DEFINE3(_lseek,unsigned int,fd,lkl_off_t,offset,unsigned int,whence)
#endif
#ifdef __lkl__NR_read
LKL_SYSCALL_DEFINE3(_read,unsigned int,fd,char *,buf,lkl_size_t,count)
#endif
#ifdef __lkl__NR_write
LKL_SYSCALL_DEFINE3(_write,unsigned int,fd,const char *,buf,lkl_size_t,count)
#endif
#ifdef __lkl__NR_pread64
LKL_SYSCALL_DEFINE4(_pread64,unsigned int,fd,char *,buf,lkl_size_t,count,lkl_loff_t,pos)
#endif
#ifdef __lkl__NR_pwrite64
LKL_SYSCALL_DEFINE4(_pwrite64,unsigned int,fd,const char *,buf,lkl_size_t,count,lkl_loff_t,pos)
#endif
#ifdef __lkl__NR_readv
LKL_SYSCALL_DEFINE3(_readv,unsigned long,fd,const struct lkl_iovec *,vec,unsigned long,vlen)
#endif
#ifdef __lkl__NR_writev
LKL_SYSCALL_DEFINE3(_writev,unsigned long,fd,const struct lkl_iovec *,vec,unsigned long,vlen)
#endif
#ifdef __lkl__NR_preadv
LKL_SYSCALL_DEFINE5(_preadv,unsigned long,fd,const struct lkl_iovec *,vec,unsigned long,vlen,unsigned long,pos_l,unsigned long,pos_h)
#endif
#ifdef __lkl__NR_preadv2
LKL_SYSCALL_DEFINE6(_preadv2,unsigned long,fd,const struct lkl_iovec *,vec,unsigned long,vlen,unsigned long,pos_l,unsigned long,pos_h,lkl_rwf_t,flags)
#endif
#ifdef __lkl__NR_pwritev
LKL_SYSCALL_DEFINE5(_pwritev,unsigned long,fd,const struct lkl_iovec *,vec,unsigned long,vlen,unsigned long,pos_l,unsigned long,pos_h)
#endif
#ifdef __lkl__NR_pwritev2
LKL_SYSCALL_DEFINE6(_pwritev2,unsigned long,fd,const struct lkl_iovec *,vec,unsigned long,vlen,unsigned long,pos_l,unsigned long,pos_h,lkl_rwf_t,flags)
#endif
#ifdef __lkl__NR_sendfile
LKL_SYSCALL_DEFINE4(_sendfile,int,out_fd,int,in_fd,lkl_off_t *,offset,lkl_size_t,count)
#endif
#ifdef __lkl__NR_sendfile64
LKL_SYSCALL_DEFINE4(_sendfile64,int,out_fd,int,in_fd,lkl_loff_t *,offset,lkl_size_t,count)
#endif
#ifdef __lkl__NR_copy_file_range
LKL_SYSCALL_DEFINE6(_copy_file_range,int,fd_in,lkl_loff_t *,off_in,int,fd_out,lkl_loff_t *,off_out,lkl_size_t,len,unsigned int,flags)
#endif
#ifdef __NR_newstat
LKL_SYSCALL_DEFINE2(_newstat,const char *,filename,struct lkl_stat *,statbuf)
#endif
#ifdef __NR_newlstat
LKL_SYSCALL_DEFINE2(_newlstat,const char *,filename,struct lkl_stat *,statbuf)
#endif
#ifdef __lkl__NR_newfstatat
LKL_SYSCALL_DEFINE4(_newfstatat,int,dfd,const char *,filename,struct lkl_stat *,statbuf,int,flag)
#endif
#ifdef __lkl__NR_newfstat
LKL_SYSCALL_DEFINE2(_newfstat,unsigned int,fd,struct lkl_stat *,statbuf)
#endif
#ifdef __lkl__NR_readlinkat
LKL_SYSCALL_DEFINE4(_readlinkat,int,dfd,const char *,pathname,char *,buf,int,bufsiz)
#endif
#ifdef __NR_readlink
LKL_SYSCALL_DEFINE3(_readlink,const char *,path,char *,buf,int,bufsiz)
#endif
#ifdef __lkl__NR_stat64
LKL_SYSCALL_DEFINE2(_stat64,const char *,filename,struct lkl_stat64 *,statbuf)
#endif
#ifdef __lkl__NR_lstat64
LKL_SYSCALL_DEFINE2(_lstat64,const char *,filename,struct lkl_stat64 *,statbuf)
#endif
#ifdef __lkl__NR_fstat64
LKL_SYSCALL_DEFINE2(_fstat64,unsigned long,fd,struct lkl_stat64 *,statbuf)
#endif
#ifdef __lkl__NR_fstatat64
LKL_SYSCALL_DEFINE4(_fstatat64,int,dfd,const char *,filename,struct lkl_stat64 *,statbuf,int,flag)
#endif
#ifdef __lkl__NR_statx
LKL_SYSCALL_DEFINE5(_statx,int,dfd,const char *,filename,unsigned,flags,unsigned int,mask,struct lkl_statx *,buffer)
#endif
#ifdef __lkl__NR_execve
LKL_SYSCALL_DEFINE3(_execve,const char *,filename,const char *const *,argv,const char *const *,envp)
#endif
#ifdef __lkl__NR_execveat
LKL_SYSCALL_DEFINE5(_execveat,int,fd,const char *,filename,const char *const *,argv,const char *const *,envp,int,flags)
#endif
#ifdef __lkl__NR_pipe2
LKL_SYSCALL_DEFINE2(_pipe2,int *,fildes,int,flags)
#endif
#ifdef __NR_pipe
LKL_SYSCALL_DEFINE1(_pipe,int *,fildes)
#endif
#ifdef __lkl__NR_mknodat
LKL_SYSCALL_DEFINE4(_mknodat,int,dfd,const char *,filename,lkl_umode_t,mode,unsigned int,dev)
#endif
#ifdef __NR_mknod
LKL_SYSCALL_DEFINE3(_mknod,const char *,filename,lkl_umode_t,mode,unsigned,dev)
#endif
#ifdef __lkl__NR_mkdirat
LKL_SYSCALL_DEFINE3(_mkdirat,int,dfd,const char *,pathname,lkl_umode_t,mode)
#endif
#ifdef __NR_mkdir
LKL_SYSCALL_DEFINE2(_mkdir,const char *,pathname,lkl_umode_t,mode)
#endif
#ifdef __NR_rmdir
LKL_SYSCALL_DEFINE1(_rmdir,const char *,pathname)
#endif
#ifdef __lkl__NR_unlinkat
LKL_SYSCALL_DEFINE3(_unlinkat,int,dfd,const char *,pathname,int,flag)
#endif
#ifdef __NR_unlink
LKL_SYSCALL_DEFINE1(_unlink,const char *,pathname)
#endif
#ifdef __lkl__NR_symlinkat
LKL_SYSCALL_DEFINE3(_symlinkat,const char *,oldname,int,newdfd,const char *,newname)
#endif
#ifdef __NR_symlink
LKL_SYSCALL_DEFINE2(_symlink,const char *,oldname,const char *,newname)
#endif
#ifdef __lkl__NR_linkat
LKL_SYSCALL_DEFINE5(_linkat,int,olddfd,const char *,oldname,int,newdfd,const char *,newname,int,flags)
#endif
#ifdef __NR_link
LKL_SYSCALL_DEFINE2(_link,const char *,oldname,const char *,newname)
#endif
#ifdef __lkl__NR_renameat2
LKL_SYSCALL_DEFINE5(_renameat2,int,olddfd,const char *,oldname,int,newdfd,const char *,newname,unsigned int,flags)
#endif
#ifdef __lkl__NR_renameat
LKL_SYSCALL_DEFINE4(_renameat,int,olddfd,const char *,oldname,int,newdfd,const char *,newname)
#endif
#ifdef __NR_rename
LKL_SYSCALL_DEFINE2(_rename,const char *,oldname,const char *,newname)
#endif
#ifdef __lkl__NR_fcntl
LKL_SYSCALL_DEFINE3(_fcntl,unsigned int,fd,unsigned int,cmd,unsigned long,arg)
#endif
#ifdef __lkl__NR_ioctl
LKL_SYSCALL_DEFINE3(_ioctl,unsigned int,fd,unsigned int,cmd,unsigned long,arg)
#endif
#ifdef __NR_getdents
LKL_SYSCALL_DEFINE3(_getdents,unsigned int,fd,struct lkl_linux_dirent *,dirent,unsigned int,count)
#endif
#ifdef __lkl__NR_getdents64
LKL_SYSCALL_DEFINE3(_getdents64,unsigned int,fd,struct lkl_linux_dirent64 *,dirent,unsigned int,count)
#endif
#ifdef __NR_select
LKL_SYSCALL_DEFINE5(_select,int,n,lkl_fd_set *,inp,lkl_fd_set *,outp,lkl_fd_set *,exp,struct lkl_timeval *,tvp)
#endif
#ifdef __lkl__NR_pselect6
LKL_SYSCALL_DEFINE6(_pselect6,int,n,lkl_fd_set *,inp,lkl_fd_set *,outp,lkl_fd_set *,exp,struct lkl_timespec *,tsp,void *,sig)
#endif
#ifdef __NR_poll
LKL_SYSCALL_DEFINE3(_poll,struct lkl_pollfd *,ufds,unsigned int,nfds,int,timeout_msecs)
#endif
#ifdef __lkl__NR_ppoll
LKL_SYSCALL_DEFINE5(_ppoll,struct lkl_pollfd *,ufds,unsigned int,nfds,struct lkl_timespec *,tsp,const lkl_sigset_t *,sigmask,lkl_size_t,sigsetsize)
#endif
#ifdef __lkl__NR_dup3
LKL_SYSCALL_DEFINE3(_dup3,unsigned int,oldfd,unsigned int,newfd,int,flags)
#endif
#ifdef __NR_dup2
LKL_SYSCALL_DEFINE2(_dup2,unsigned int,oldfd,unsigned int,newfd)
#endif
#ifdef __lkl__NR_dup
LKL_SYSCALL_DEFINE1(_dup,unsigned int,fildes)
#endif
#ifdef __lkl__NR_umount
LKL_SYSCALL_DEFINE2(_umount,char *,name,int,flags)
#endif
#ifdef __lkl__NR_mount
LKL_SYSCALL_DEFINE5(_mount,char *,dev_name,char *,dir_name,char *,type,unsigned long,flags,void *,data)
#endif
#ifdef __lkl__NR_pivot_root
LKL_SYSCALL_DEFINE2(_pivot_root,const char *,new_root,const char *,put_old)
#endif
#ifdef __lkl__NR_setxattr
LKL_SYSCALL_DEFINE5(_setxattr,const char *,pathname,const char *,name,const void *,value,lkl_size_t,size,int,flags)
#endif
#ifdef __lkl__NR_lsetxattr
LKL_SYSCALL_DEFINE5(_lsetxattr,const char *,pathname,const char *,name,const void *,value,lkl_size_t,size,int,flags)
#endif
#ifdef __lkl__NR_fsetxattr
LKL_SYSCALL_DEFINE5(_fsetxattr,int,fd,const char *,name,const void *,value,lkl_size_t,size,int,flags)
#endif
#ifdef __lkl__NR_getxattr
LKL_SYSCALL_DEFINE4(_getxattr,const char *,pathname,const char *,name,void *,value,lkl_size_t,size)
#endif
#ifdef __lkl__NR_lgetxattr
LKL_SYSCALL_DEFINE4(_lgetxattr,const char *,pathname,const char *,name,void *,value,lkl_size_t,size)
#endif
#ifdef __lkl__NR_fgetxattr
LKL_SYSCALL_DEFINE4(_fgetxattr,int,fd,const char *,name,void *,value,lkl_size_t,size)
#endif
#ifdef __lkl__NR_listxattr
LKL_SYSCALL_DEFINE3(_listxattr,const char *,pathname,char *,list,lkl_size_t,size)
#endif
#ifdef __lkl__NR_llistxattr
LKL_SYSCALL_DEFINE3(_llistxattr,const char *,pathname,char *,list,lkl_size_t,size)
#endif
#ifdef __lkl__NR_flistxattr
LKL_SYSCALL_DEFINE3(_flistxattr,int,fd,char *,list,lkl_size_t,size)
#endif
#ifdef __lkl__NR_removexattr
LKL_SYSCALL_DEFINE2(_removexattr,const char *,pathname,const char *,name)
#endif
#ifdef __lkl__NR_lremovexattr
LKL_SYSCALL_DEFINE2(_lremovexattr,const char *,pathname,const char *,name)
#endif
#ifdef __lkl__NR_fremovexattr
LKL_SYSCALL_DEFINE2(_fremovexattr,int,fd,const char *,name)
#endif
#ifdef __lkl__NR_vmsplice
LKL_SYSCALL_DEFINE4(_vmsplice,int,fd,const struct lkl_iovec *,iov,unsigned long,nr_segs,unsigned int,flags)
#endif
#ifdef __lkl__NR_splice
LKL_SYSCALL_DEFINE6(_splice,int,fd_in,lkl_loff_t *,off_in,int,fd_out,lkl_loff_t *,off_out,lkl_size_t,len,unsigned int,flags)
#endif
#ifdef __lkl__NR_tee
LKL_SYSCALL_DEFINE4(_tee,int,fdin,int,fdout,lkl_size_t,len,unsigned int,flags)
#endif
#ifdef __lkl__NR_sync
LKL_SYSCALL_DEFINE0(_sync,)
#endif
#ifdef __lkl__NR_syncfs
LKL_SYSCALL_DEFINE1(_syncfs,int,fd)
#endif
#ifdef __lkl__NR_fsync
LKL_SYSCALL_DEFINE1(_fsync,unsigned int,fd)
#endif
#ifdef __lkl__NR_fdatasync
LKL_SYSCALL_DEFINE1(_fdatasync,unsigned int,fd)
#endif
#ifdef __lkl__NR_sync_file_range
LKL_SYSCALL_DEFINE4(_sync_file_range,int,fd,lkl_loff_t,offset,lkl_loff_t,nbytes,unsigned int,flags)
#endif
#ifdef __lkl__NR_sync_file_range2
LKL_SYSCALL_DEFINE4(_sync_file_range2,int,fd,unsigned int,flags,lkl_loff_t,offset,lkl_loff_t,nbytes)
#endif
#ifdef __lkl__NR_utimensat
LKL_SYSCALL_DEFINE4(_utimensat,int,dfd,const char *,filename,struct lkl_timespec *,utimes,int,flags)
#endif
#ifdef __NR_futimesat
LKL_SYSCALL_DEFINE3(_futimesat,int,dfd,const char *,filename,struct lkl_timeval *,utimes)
#endif
#ifdef __NR_utimes
LKL_SYSCALL_DEFINE2(_utimes,char *,filename,struct lkl_timeval *,utimes)
#endif
#ifdef __lkl__NR_getcwd
LKL_SYSCALL_DEFINE2(_getcwd,char *,buf,unsigned long,size)
#endif
#ifdef __lkl__NR_statfs
LKL_SYSCALL_DEFINE2(_statfs,const char *,pathname,struct lkl_statfs *,buf)
#endif
#ifdef __lkl__NR_statfs64
LKL_SYSCALL_DEFINE3(_statfs64,const char *,pathname,lkl_size_t,sz,struct lkl_statfs64 *,buf)
#endif
#ifdef __lkl__NR_fstatfs
LKL_SYSCALL_DEFINE2(_fstatfs,unsigned int,fd,struct lkl_statfs *,buf)
#endif
#ifdef __lkl__NR_fstatfs64
LKL_SYSCALL_DEFINE3(_fstatfs64,unsigned int,fd,lkl_size_t,sz,struct lkl_statfs64 *,buf)
#endif
#ifdef __NR_ustat
LKL_SYSCALL_DEFINE2(_ustat,unsigned,dev,struct lkl_ustat *,ubuf)
#endif
#ifdef __NR_bdflush
LKL_SYSCALL_DEFINE2(_bdflush,int,func,long,data)
#endif
#ifdef __lkl__NR_epoll_create1
LKL_SYSCALL_DEFINE1(_epoll_create1,int,flags)
#endif
#ifdef __NR_epoll_create
LKL_SYSCALL_DEFINE1(_epoll_create,int,size)
#endif
#ifdef __lkl__NR_epoll_ctl
LKL_SYSCALL_DEFINE4(_epoll_ctl,int,epfd,int,op,int,fd,struct lkl_epoll_event *,event)
#endif
#ifdef __NR_epoll_wait
LKL_SYSCALL_DEFINE4(_epoll_wait,int,epfd,struct lkl_epoll_event *,events,int,maxevents,int,timeout)
#endif
#ifdef __lkl__NR_epoll_pwait
LKL_SYSCALL_DEFINE6(_epoll_pwait,int,epfd,struct lkl_epoll_event *,events,int,maxevents,int,timeout,const lkl_sigset_t *,sigmask,lkl_size_t,sigsetsize)
#endif
#ifdef __lkl__NR_eventfd2
LKL_SYSCALL_DEFINE2(_eventfd2,unsigned int,count,int,flags)
#endif
#ifdef __NR_eventfd
LKL_SYSCALL_DEFINE1(_eventfd,unsigned int,count)
#endif
#ifdef __lkl__NR_flock
LKL_SYSCALL_DEFINE2(_flock,unsigned int,fd,unsigned int,cmd)
#endif
#ifdef __lkl__NR_name_to_handle_at
LKL_SYSCALL_DEFINE5(_name_to_handle_at,int,dfd,const char *,name,struct file_handle *,handle,int *,mnt_id,int,flag)
#endif
#ifdef __lkl__NR_open_by_handle_at
LKL_SYSCALL_DEFINE3(_open_by_handle_at,int,mountdirfd,struct file_handle *,handle,int,flags)
#endif
#ifdef __lkl__NR_ioprio_set
LKL_SYSCALL_DEFINE3(_ioprio_set,int,which,int,who,int,ioprio)
#endif
#ifdef __lkl__NR_ioprio_get
LKL_SYSCALL_DEFINE2(_ioprio_get,int,which,int,who)
#endif
#ifdef __lkl__NR_getrandom
LKL_SYSCALL_DEFINE3(_getrandom,char *,buf,lkl_size_t,count,unsigned int,flags)
#endif
#ifdef __lkl__NR_socket
LKL_SYSCALL_DEFINE3(_socket,int,family,int,type,int,protocol)
#endif
#ifdef __lkl__NR_socketpair
LKL_SYSCALL_DEFINE4(_socketpair,int,family,int,type,int,protocol,int *,usockvec)
#endif
#ifdef __lkl__NR_bind
LKL_SYSCALL_DEFINE3(_bind,int,fd,struct lkl_sockaddr *,umyaddr,int,addrlen)
#endif
#ifdef __lkl__NR_listen
LKL_SYSCALL_DEFINE2(_listen,int,fd,int,backlog)
#endif
#ifdef __lkl__NR_accept4
LKL_SYSCALL_DEFINE4(_accept4,int,fd,struct lkl_sockaddr *,upeer_sockaddr,int *,upeer_addrlen,int,flags)
#endif
#ifdef __lkl__NR_accept
LKL_SYSCALL_DEFINE3(_accept,int,fd,struct lkl_sockaddr *,upeer_sockaddr,int *,upeer_addrlen)
#endif
#ifdef __lkl__NR_connect
LKL_SYSCALL_DEFINE3(_connect,int,fd,struct lkl_sockaddr *,uservaddr,int,addrlen)
#endif
#ifdef __lkl__NR_getsockname
LKL_SYSCALL_DEFINE3(_getsockname,int,fd,struct lkl_sockaddr *,usockaddr,int *,usockaddr_len)
#endif
#ifdef __lkl__NR_getpeername
LKL_SYSCALL_DEFINE3(_getpeername,int,fd,struct lkl_sockaddr *,usockaddr,int *,usockaddr_len)
#endif
#ifdef __lkl__NR_sendto
LKL_SYSCALL_DEFINE6(_sendto,int,fd,void *,buff,lkl_size_t,len,unsigned int,flags,struct lkl_sockaddr *,addr,int,addr_len)
#endif
#ifdef __NR_send
LKL_SYSCALL_DEFINE4(_send,int,fd,void *,buff,lkl_size_t,len,unsigned int,flags)
#endif
#ifdef __lkl__NR_recvfrom
LKL_SYSCALL_DEFINE6(_recvfrom,int,fd,void *,ubuf,lkl_size_t,size,unsigned int,flags,struct lkl_sockaddr *,addr,int *,addr_len)
#endif
#ifdef __NR_recv
LKL_SYSCALL_DEFINE4(_recv,int,fd,void *,ubuf,lkl_size_t,size,unsigned int,flags)
#endif
#ifdef __lkl__NR_setsockopt
LKL_SYSCALL_DEFINE5(_setsockopt,int,fd,int,level,int,optname,char *,optval,int,optlen)
#endif
#ifdef __lkl__NR_getsockopt
LKL_SYSCALL_DEFINE5(_getsockopt,int,fd,int,level,int,optname,char *,optval,int *,optlen)
#endif
#ifdef __lkl__NR_shutdown
LKL_SYSCALL_DEFINE2(_shutdown,int,fd,int,how)
#endif
#ifdef __lkl__NR_sendmsg
LKL_SYSCALL_DEFINE3(_sendmsg,int,fd,struct lkl_user_msghdr *,msg,unsigned int,flags)
#endif
#ifdef __lkl__NR_sendmmsg
LKL_SYSCALL_DEFINE4(_sendmmsg,int,fd,struct lkl_mmsghdr *,mmsg,unsigned int,vlen,unsigned int,flags)
#endif
#ifdef __lkl__NR_recvmsg
LKL_SYSCALL_DEFINE3(_recvmsg,int,fd,struct lkl_user_msghdr *,msg,unsigned int,flags)
#endif
#ifdef __lkl__NR_recvmmsg
LKL_SYSCALL_DEFINE5(_recvmmsg,int,fd,struct lkl_mmsghdr *,mmsg,unsigned int,vlen,unsigned int,flags,struct lkl_timespec *,timeout)
#endif
