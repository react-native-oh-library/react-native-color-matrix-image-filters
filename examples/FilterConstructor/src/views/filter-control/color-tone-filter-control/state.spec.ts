import { cleanup, renderHook, act } from '@testing-library/react'
import { useBacklash } from 'react-use-backlash'
import { ColorToneFilter } from '../../../domain/filters/types'
import { Util } from '../../../util'
import { init, updates } from './state'

const { getActions, getState } = Util.TestUtil

describe('ColorToneControl', () => {
  afterEach(cleanup)

  test('state', async () => {
    const filter = {
      tag: 'ColorTone' as const,
      desaturation: 0,
      toned: 0,
      darkColor: 'red',
      lightColor: 'blue'
    }

    const update = ({ desaturation, toned, darkColor, lightColor }: ColorToneFilter) => {
      filter.desaturation = desaturation
      filter.toned = toned
      filter.darkColor = darkColor
      filter.lightColor = lightColor
    }

    const hook = renderHook(() => useBacklash(init, updates, { ...filter, update }))

    const actions = getActions(hook)

    expect(getState(hook)).toEqual(undefined)

    await act(() => {
      actions.changeDesaturation(10)
    })

    expect(filter.desaturation).toEqual(10)

    await act(() => {
      actions.changeToned(15)
    })

    expect(filter.toned).toEqual(15)

    await act(() => {
      actions.selectDarkColor('white')
    })

    expect(filter.darkColor).toEqual('white')

    await act(() => {
      actions.selectLightColor('black')
    })

    expect(filter.lightColor).toEqual('black')
  })
})
