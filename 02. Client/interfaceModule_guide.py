# Add to the imports:
if app.ENABLE_AURA_SYSTEM:
	import uiAura

# Add the following to the bottom of the __MakeWindows function:
		if app.ENABLE_AURA_SYSTEM:
			wndAura = uiAura.AuraWindow()
			self.wndAura = wndAura

# In the MakeInterface function, extend the tooltipbindings to the other classes with the following:
		if app.ENABLE_AURA_SYSTEM:
			self.wndAura.SetItemToolTip(self.tooltipItem)

# Add the following to the Close function:
		if app.ENABLE_AURA_SYSTEM:
			if self.wndAura:
				self.wndAura.Destroy()
			del self.wndAura

# Paste the next code into the RefreshInventory function:
		if app.ENABLE_AURA_SYSTEM:
			if player.IsAuraRefineWindowOpen():
				if self.wndAura and self.wndAura.IsShow():
					self.wndAura.RefreshAuraWindow()

# Add the next one into the HideAllWindows function:
		if app.ENABLE_AURA_SYSTEM:
			if self.wndAura:
				self.wndAura.Hide()

# Add the following to the beginning of the OpenPrivateShopInputNameDialog and OpenPrivateShopBuilder functions:
		if app.ENABLE_AURA_SYSTEM:
			if self.wndAura and self.wndAura.IsShow():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.AURA_OPEN_OTHER_WINDOW)
				return

# Add anywhere inside of the Interface class:
	if app.ENABLE_AURA_SYSTEM:
		def AuraWindowOpen(self, type):
			if self.wndAura.IsShow():
				return

			if self.inputDialog or self.privateShopBuilder.IsShow():# or shop.GetNameDialogOpen():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.ACCE_NOT_OPEN_PRIVATE_SHOP)
				return

			if self.dlgRefineNew and self.dlgRefineNew.IsShow():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.ACCE_NOT_OPEN_REFINE)
				return

			self.wndAura.Open(type)

			if not self.wndInventory.IsShow():
				self.wndInventory.Show()

		def AuraWindowClose(self):
			if not self.wndAura.IsShow():
				return

			self.wndAura.CloseWindow()
