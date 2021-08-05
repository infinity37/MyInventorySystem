---@class UserWidget
local weaponwidget={}
function weaponwidget:Initialize()
end

function weaponwidget:RemoveWeaponFromSlot() 
    if (self.WeaponItem == nil) then
        return;
    end
    local mypc = self:GetOwningPlayer()
    local backpack = mypc.MyBackPack
    backpack:RemoveFromWeaponSlot(self.SoltId)
    local mypl = self:GetOwningPlayerPawn()
    mypl:RefreshBagUI()
end

function weaponwidget:DropWeaponFromSlot()
    if (self.WeaponItem == nil) then
        return;
    end
    local mypc = self:GetOwningPlayer()
    local backpack = mypc.MyBackPack
    backpack:RemoveFromWeaponSlot(self.SoltId)
    backpack:DropItem(self.WeaponItem.ItemTypeId, 1)  
    local mypl = self:GetOwningPlayerPawn()
    mypl:RefreshBagUI()
end

return weaponwidget