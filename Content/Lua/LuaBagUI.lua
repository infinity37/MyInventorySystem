---@class UserWidget
local bagui = {}
local wll = import("WidgetLayoutLibrary")
local sbl = import("SlateBlueprintLibrary")
local kml = import("KismetMathLibrary")

function bagui:Initialize()
end

function bagui:RefreshBagUI() 
    self.UINormalSpace:LoadItems()
    self.UIWeaponSlot:LoadWeaponSlot()
    self.UIWeaponSlot:LoadAttachmentSlot()
end

function bagui:InitSlotId()
    self.UIWeaponSlot.WeaponWidget1.SoltId = 0
    self.UIWeaponSlot.WeaponWidget2.SoltId = 1
    self.UIWeaponSlot.AttachmentWidget1.SlotId = 0
    self.UIWeaponSlot.AttachmentWidget2.SlotId = 1
    self.UIWeaponSlot.AttachmentWidget3.SlotId = 2
    self.UIWeaponSlot.AttachmentWidget4.SlotId = 3
end

function bagui:switchSlot()
    self:UnEquipWeaponInSlot(self.EquipedSlot)
    self:EquipWeaponInSlot(1-self.EquipedSlot)
    self.EquipedSlot = 1-self.EquipedSlot
end

function bagui:EquipedWeaponReload() 
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
            self:RefreshBagUI()
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

function bagui:IsDragBackOperation(DropPositionX, MyGeometry)
    --local cpsNormalSpace = wll.SlotAsCanvasSlot(self.UINormalSpace)
    print("TestDragBack")
    local vector1 = wll.SlotAsCanvasSlot(self.UINormalSpace):GetPosition()
    local vector2 = sbl.GetLocalSize(MyGeometry)
    local nowposx,nowposy = kml.BreakVector2D(vector1 + vector2, nowposx, nowposy)
    print(nowposx)
    if (nowposx < DropPositionX)
    then
        return true;
    else
        return false;
    end
end

function bagui:IsDropOperation(DropPositionX, MyGeometry)
    local vector1 = wll.SlotAsCanvasSlot(self.UIWeaponSlot):GetPosition()
    local vector2 = sbl.GetLocalSize(MyGeometry)
    local nowposx, nowposy = kml.BreakVector2D(vector1 + vector2, nowposx, nowposy)
    if (nowposx > DropPositionX) then
        return true;
    else
        return false;
    end
end

function bagui:IsSlotOperation(DropPositionX, DropPositionY, MyGeometry)
    local wsVector = wll.SlotAsCanvasSlot(self.UIWeaponSlot):GetPosition() + sbl.GetLocalSize(MyGeometry)
    local nsVector = wll.SlotAsCanvasSlot(self.UINormalSpace):GetPosition() + sbl.GetLocalSize(MyGeometry)
    local wsx, wsy = kml.BreakVector2D(wsVector, wsx, wsy)
    local nsx, nsy = kml.BreakVector2D(nsVector, nsx, nsy)
    if (DropPositionX < nsx and DropPositionX > wsx) then
        local wssize = wll.SlotAsCanvasSlot(self.UIWeaponSlot):GetSize()
        local wsw, wsh = kml.BreakVector2D(wssize, wsw,wsh)
        if (DropPositionY < wsh / 2) then 
            return 0
        else
            if (DropPositionY < wsh) then
                return 1;
            end
        end
    end
    return -1;
end

return bagui