## 设置退出时终端光标改为竖线闪烁

写在 `init.lua` 中。

```lua
-- 退出 Neovim 时恢复闪烁竖线光标
vim.api.nvim_create_autocmd('VimLeave', {
  callback = function()
    vim.opt.guicursor = "a:ver25-blinkwait700-blinkon400-blinkoff250"
  end,
})
```

