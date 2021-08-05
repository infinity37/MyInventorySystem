---@class UserWidget
local bagui = {}

function bagui:Initialize()
end

function bagui:RefreshBagUI() 
    print("LuaRefresh")
    self.UINormalSpace:LoadItems()
    self.UIWeaponSlot:LoadWeaponSlot()
    self.UIWeaponSlot:LoadAttachmentSlot()
end

function bagui:InitSlotId()
    print("InitSlotId")
    self.UIWeaponSlot.WeaponWidget1.SoltId = 0
    self.UIWeaponSlot.WeaponWidget2.SoltId = 1
    self.UIWeaponSlot.AttachmentWidget1.SlotId = 0
    self.UIWeaponSlot.AttachmentWidget2.SlotId = 1
    self.UIWeaponSlot.AttachmentWidget3.SlotId = 2
    self.UIWeaponSlot.AttachmentWidget4.SlotId = 3
end

function bagui:switchSlot()
    print("SwitchSlot")
    self:UnEquipWeaponInSlot(self.EquipedSlot)
    self:EquipWeaponInSlot(1-self.EquipedSlot)
    self.EquipedSlot = 1-self.EquipedSlot
end

function bagui:EquipedWeaponReload() 
    print("Reload")
    local mypc = self:GetOwningPlayer()
    local backpack = mypc.MyBackPack
    if (backpack.WeaponSlot:Get(self.EquipedSlot) ~= nil) then
        local myweapon = backpack.WeaponSlot:Get(self.EquipedSlot)
        myweapon:Reload()
        self:RefreshBagUI()
    end
end

function bagui:EquipWeaponInSlot(SlotId)
    local backpack = self:GetOwningPlayer().MyBackPack
    if (backpack.WeaponSlot:Get(SlotId) ~= nil) then
        local weapontoequip = backpack.WeaponSlot:Get(SlotId)
        if (weapontoequip:IsEquiped() ~= true) then 
            weapontoequip:EquipItem()
            local myplayer = self:GetOwningPlayerPawn()
            myplayer:AttachWeapon(weapontoequip.ItemTypeId)
            return true;
        end
    end
    return false
end

function bagui:UnEquipWeaponInSlot(SlotId)
    local backpack = self:GetOwningPlayer().MyBackPack
    if (backpack.WeaponSlot:Get(SlotId) ~= nil) then
        local weapontoequip = backpack.WeaponSlot:Get(SlotId)
        if (weapontoequip:IsEquiped() == true) then 
            weapontoequip:UnEquipItem()
            local myplayer = self:GetOwningPlayerPawn()
            myplayer:DetachWeapon(weapontoequip.ItemTypeId)
        end
    end
end

return bagui