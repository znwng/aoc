local x, y = 0, 0
local facing = 0

local result = {}
local visited = {}

for line in io.lines("./input.txt") do
	for value in string.gmatch(line, "[^,]+") do
		value = value:match("^%s*(.-)%s*$")
		table.insert(result, value)
	end
end

local first_repeat = nil

local function visit(x, y)
	local key = x .. "," .. y
	if visited[key] then
		return key
	else
		visited[key] = true
		return nil
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

	for i = 1, steps do
		if facing == 0 then
			y = y + 1
		elseif facing == 1 then
			x = x + 1
		elseif facing == 2 then
			y = y - 1
		elseif facing == 3 then
			x = x - 1
		end

		if not first_repeat then
			local repeat_key = visit(x, y)
			if repeat_key then
				first_repeat = { x = x, y = y }
			end
		end
	end
end

if first_repeat then
	print(first_repeat.x .. "," .. first_repeat.y)
	print(math.abs(first_repeat.x) + math.abs(first_repeat.y))
else
	print("No repeated coordinate found")
end

