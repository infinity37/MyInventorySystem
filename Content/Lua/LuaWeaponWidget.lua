---@class UserWidget
local weaponwidget={}
local WBL = import("WidgetBlueprintLibrary")
local KIL = import("KismetInputLibrary")
local SBL = import("SlateBlueprintLibrary")
local GameplayStatics=import'GameplayStatics';

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


local FKey = import "Key"
function weaponwidget:OnMouseButtonDown(MyGeometry, MouseEvent)
    ---print("OnMouseOverride")
    local cursorpos = KIL.PointerEvent_GetScreenSpacePosition(MouseEvent)
    self.DragOffset = SBL.AbsolutetoLocal(MyGeometry, cursorpos)
    local pressedbutton = KIL.PointerEvent_GetEffectingButton(MouseEvent)
    local key = FKey()
    key.KeyName = "LeftMouseButton"
    return WBL.DetectDragIfPressed(MouseEvent,self,key)
end

function weaponwidget:GetHaveWeapon()
    if (self.WeaponItem ~= nil) then
        return tostring('/')
    else
        return tostring('')
    end
end

function weaponwidget:GetAmmoTypeText()
    local gamestate = GameplayStatics.GetGameState(self)
    local infotable = gamestate:GetItemInfoTable()
    if (self.WeaponItem ~= nil) then
        local ammoname = infotable:GetItemInfoById(self.WeaponItem.AmmoType)
        return tostring(ammoname.ItemName)
    end
end

return weaponwidget