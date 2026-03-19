local x, y = 0, 0
local facing = 0 -- n0 e1 s2 w3

local result = {}

for line in io.lines("./input.txt") do
	for value in string.gmatch(line, "[^,]+") do
		value = value:match("^%s*(.-)%s*$")
		table.insert(result, value)
	end
end

for _, v in ipairs(result) do
	local turn, steps = v:match("^(%a)(%d+)$")
	steps = tonumber(steps)

	if turn == "R" then
		facing = (facing + 1) % 4
	elseif turn == "L" then
		facing = (facing + 3) % 4
	else
		error("Invalid turn: " .. turn)
	end

	if facing == 0 then
		y = y + steps
	elseif facing == 1 then
		x = x + steps
	elseif facing == 2 then
		y = y - steps
	elseif facing == 3 then
		x = x - steps
	end
end

local distance = math.abs(x) + math.abs(y)
print(distance)

