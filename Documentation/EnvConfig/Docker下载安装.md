# Docker下载安装

## Ubuntu下Docker的安装

### 卸载默认安装

```bash
sudo apt-get remove docker docker-engine docker.io containerd runc
```

### 安装必要支持

```bash
sudo apt install apt-transport-https ca-certificates curl software-properties-common gnupg lsb-release
```

### 配置`GPG key`

添加 Docker 阿里源 `GPG key`

```bash
curl -fsSL https://mirrors.aliyun.com/docker-ce/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
```

阿里apt源

```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://mirrors.aliyun.com/docker-ce/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list &gt; /dev/null
```

更新源

```bash
sudo apt update && sudo apt-get update
```

### 安装Docker

安装最新版本的 `Docker`

```bash
sudo apt install docker-ce docker-ce-cli containerd.io
```

查看 `Docker` 版本

```bash
sudo docker version
```

查看 `Docker` 运行状态

```bash
sudo systemctl status docker
```

### 配置`docker hub mirror`

拉取失败的解决方法：

```bash
[root@localhost ~]# docker pull zookeeper
Using default tag: latest
Error response from daemon: Get "https://registry-1.docker.io/v2/": net/http: request canceled while waiting for connection (Client.Timeout exceeded while awaiting headers)
```

将可用的镜像仓库地址写入到 `/etc/docker/daemon.json` 配置文件中

```bash
vim /etc/docker/daemon.json
```

```bash
{
    "registry-mirrors": [
        "https://2a6bf1988cb6428c877f723ec7530dbc.mirror.swr.myhuaweicloud.com",
        "https://docker.m.daocloud.io",
        "https://hub-mirror.c.163.com",
        "https://mirror.baidubce.com",
        "https://your_preferred_mirror",
        "https://dockerhub.icu",
        "https://docker.registry.cyou",
        "https://docker-cf.registry.cyou",
        "https://dockercf.jsdelivr.fyi",
        "https://docker.jsdelivr.fyi",
        "https://dockertest.jsdelivr.fyi",
        "https://mirror.aliyuncs.com",
        "https://dockerproxy.com",
        "https://mirror.baidubce.com",
        "https://docker.m.daocloud.io",
        "https://docker.nju.edu.cn",
        "https://docker.mirrors.sjtug.sjtu.edu.cn",
        "https://docker.mirrors.ustc.edu.cn",
        "https://mirror.iscas.ac.cn",
        "https://docker.rainbond.cc"
    ]
}
```

将上面配置写入文件后执行以下命令

重新加载一下 `docker` 的配置文件

```bash
systemctl daemon-reload
```

重启`docker`服务

```bash
systemctl restart docker.service
```

### 安装Docker 命令补全工具

```bash
sudo apt-get install bash-completion
```

```bash
sudo curl -L https://raw.githubusercontent.com/docker/docker-ce/master/components/cli/contrib/completion/bash/docker -o /etc/bash_completion.d/docker.sh
```

```bash
source /etc/bash_completion.d/docker.sh
```

### 允许非Root用户执行docker 命令

添加docker用户组

```bash
sudo groupadd docker
```

将当前用户添加到用户组

```bash
sudo usermod -aG docker $USER
```

权限生效

```bash
newgrp docker
```

查看所有容器

```bash
docker ps -a
```

更新 `.bashrc` 文件

我们需要编辑 `~/.bashrc` 文件，并在文件末尾增加如下一行(避免每次都要重新输入`newgrp docker`)

```bash
groupadd -f docker
```

## 总结

每个命令都可以直接复制运行，这是Ubuntu下的docker的安装步骤。
