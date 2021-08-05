---@class UserWidget
local itemwidget = {}
local WBL = import("WidgetBlueprintLibrary")
local KIL = import("KismetInputLibrary")
local SBL = import("SlateBlueprintLibrary")

function itemwidget:Initialize()

end

function itemwidget:UseItemFunction()
    local mypc = self:GetOwningPlayer()
    local backpack = mypc.MyBackPack
    ----print(self.ItemTypeId)
    backpack:UseItem(self.ItemTypeId)
    if (mypc:GetItemCountById(self.ItemTypeId) <= 0) then
        self:RemoveFromParent()
    end
end

local uiclass = slua.loadUI('/Game/UI/DropCountBox.DropCountBox')
function itemwidget:DropItemFunction()
    self.Super:DropItemFunction()
end

function itemwidget:AddWeaponToSlot(SlotId) 
    local mypc = self:GetOwningPlayer()
    local mypp = self:GetOwningPlayerPawn()
    local backpack = mypc.MyBackPack
    backpack:AddToWeaponSlot(self.ItemTypeId, SlotId)
    mypp:RefreshBagUI()
end

function itemwidget:AddAttachmentToSlot(SlotId) 
    local mypc = self:GetOwningPlayer()
    local mypp = self:GetOwningPlayerPawn()
    local backpack = mypc.MyBackPack
    backpack:AddToAttachmentSlot(self.ItemTypeId, SlotId)
    mypp:RefreshBagUI()
end

function itemwidget:OnMouseEnter(MyGeometry,MouseEvent)
    local myborder = self.WidgetSizeBox
    myborder:SetHeightOverride(150.0)
    self.ButtonDrop:SetVisibility(0)
    self.ButtonUse:SetVisibility(0)
end

function itemwidget:OnMouseLeave(MouseEvent)
    local myborder = self.WidgetSizeBox
    myborder:SetHeightOverride(110.0)
    self.ButtonDrop:SetVisibility(2)
    self.ButtonUse:SetVisibility(2)
end

local FKey = import "Key"
function itemwidget:OnMouseButtonDown(MyGeometry, MouseEvent)
    ---print("OnMouseOverride")
    local cursorpos = KIL.PointerEvent_GetScreenSpacePosition(MouseEvent)
    self.DragOffset = SBL.AbsolutetoLocal(MyGeometry, cursorpos)
    local key = FKey()
    key.KeyName = "LeftMouseButton"
    return WBL.DetectDragIfPressed(MouseEvent,self,key)
end

return itemwidget