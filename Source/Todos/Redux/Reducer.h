// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions.h"

enum class EActionType;
class UAppState;
class UAction;

template <typename StateType>
class FReducer
{
public:
	FReducer() {}
	virtual ~FReducer() {}

	virtual const StateType* GetInitialState() const = 0;
	virtual const StateType* Reduce(const StateType* State, const UAction* Action) const = 0;
};

template <typename StateType>
class FLeafReducer : public FReducer<StateType>
{
public:
	FLeafReducer() {}
	virtual ~FLeafReducer() {}

	typedef const StateType*(ActionHandlerType)(const StateType* State, const UAction* Action);

	virtual const StateType* Reduce(const StateType* State, const UAction* Action) const
	{
		check(State && Action);

		const TFunction<ActionHandlerType>* Handler = ActionHandlers.Find(Action->GetType());
		if (Handler)
		{
			return (*Handler)(State, Action);
		}
		return State;
	}

protected:
	void Register(EActionType ActionType, ActionHandlerType Handler)
	{
		ActionHandlers.Add(ActionType, Handler);
	}

private:
	TMap<EActionType, TFunction<ActionHandlerType>> ActionHandlers;
};
