---@class UserWidget
local normalspace = {}

function normalspace:Initialize()

end

function normalspace:LoadItems()
    print("Slua:LoadItems")
    self.NormalSpaceBox:ClearChildren()
    self.EndOfData = false
    local PageStart = self.PageNum * 9
    local PageEnd = PageStart + 18
    local cnt = 0
    local MyBackPack = self:GetOwningPlayer().MyBackPack
    local ItemLength = MyBackPack.NormalSpace:Num()
    for i,v in pairs(MyBackPack.NormalSpace) do
        print("arr item",i,v)
        if (cnt >= PageEnd) then
            break
        end
        if (ItemLength - 1 == i) then
            self.EndOfData = true
        end
        local ItemType = math.modf(v.ItemTypeId/100);
        if ((self.TypeNum == 0 or self.TypeNum == ItemType) and (v.ItemInSlot < 0 and v.ItemCount > 0)) 
        then
            cnt = cnt + 1
            if (cnt >= PageStart and cnt < PageEnd) then
                self:AddItem(v)
            end
        end
    end
end

return normalspace